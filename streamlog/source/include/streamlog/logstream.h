// -*- mode: c++;
#ifndef logstream_h
#define logstream_h

#include "streamlog/prefix.h"

#include <iostream>
#include <map>
#include <mutex>

namespace streamlog{

  class prefix_base ;
  class logscope ;

/** Thread safe helper class that collects streamed data 
 *  and sends it to the actual ostream on deletion.
 */
  class printthread: public std::ostringstream {
  protected:
    std::ostringstream _oss{} ;
    std::string _pref{};
    std::ostream* _o = nullptr ;
  public:
    /// returns an invalid stream
    printthread() : printthread::basic_ios( 0 ) {} ;
    /// initialize w/ prefix and final ostream
    printthread(std::string prefix,std::ostream* o):_pref(prefix),_o(o){};
    /// copy c'tor copies stringbugf from local stringstream
    printthread( printthread&& rhs ){
      printthread::basic_ostream<char>( rhs.rdbuf() ) ;
    }
    /// on deletion we actually write to the output
    ~printthread(){

      //FIXME: here we need to prepend the prefix to every newline before dumping to ostream

      std::lock_guard<std::mutex> guard(_mutexPrint);
        *_o << _pref << this->str() ;
      }
  private:
    static std::mutex _mutexPrint;
  };


/** Class defining a log stream that is used to print log messages depending
   *  on current log level. Can be initialized with any std::ostream, typically either 
   *  std::cout or an std::ofstream file handler.
   *  There is one global instance of this class defined in the library: logstream::out  <br>
   *  Typically only this instance is needed, e.g.: <br>
   *  <pre>
   *    // in int main() :
   *    streamlog::out.init( std::cout, argv[0] ) ;
   * 
   *    //...
   *    
   *    if( streamlog::out.write< streamlog::DEBUG1 >() )
   *       streamlog::out() << " this message will only be printed if level >= DEBUG1::level " 
   *                        << std::endl ;
   * 
   *    // or the same, simply using a macro:
   * 
   *    streamlog_out( DEBUG )  << " this message will only be printed if level >= DEBUG1::level " 
   *                            << std::endl ;
   * 
   *    
   *  </pre>
   *  Note that with the above calling sequence or the macro no runtime overhead is created
   *  if streamlog::DEBUG1::active is false and else if the log level is smaller than 
   *  streamlog::DEBUG1::level no formatting of the message will happen, i.e. also very little 
   *  runtime cost is involved. <br>
   *  the behaviour of the logstream, i.e. the current log level and log scope name can be changed only
   *  through an object of streamlog::logscope.
   * 
   *  @see logstream::write() 
   *  @see logscope
   *
   *  @author F. Gaede, DESY
   *  @version $Id: logstream.h,v 1.3 2007-08-08 13:08:34 gaede Exp $
   */
  class logstream {

    friend class logscope ;
    typedef std::map< std::string,  unsigned > LevelMap ;

  public :

    logstream() ; 
    logstream(const logstream&) = delete ;
    logstream& operator=(const logstream&) = delete ;
    ~logstream() ;

    /** Initialize the logstream with an std::ostream, e.g. std::cout and 
     *  the main scope name, e.g. argv[0].
     *  Only first call to this method has an effect, subsequent calls are ignored.
     * 
     */
    void init( std::ostream& os , const std::string name ) ;

   /** True if next log message of the current level (class T ) will be written, i.e.
     *  the next call to std::ostream& operator()() will return a valid outstream.
     * 
     */
    template<class T>
    inline bool write() {
      
      // dont' call chek_level if T::active == false
      return (  T::active   &&    check_level<T>()  ) ;
    }

    /** True if next log message of the current level (class T ) would be written
     *  - can be used to conditionally execute code blocks that are needed before writing to
     * the outstream.
     * 
     */
    template<class T>
    inline bool would_write() {
      
      return (  T::active   &&  T::level >= _level ) ;
    }

   /** Return the actual std::ostream where the message should be writen to - will return
     *  a nullstream unless prepended by a successfull call to write<MESSAGELEVEL>()
     */
    printthread operator()() ;

    /** Adds a level name to the stream for setting the log level with a string through 
     *  a scope class. Only names added with this method will have an effect - other log 
     *  levels can only be activated with logstream::logscope::setLevel<T>().
     *  Useful for framework programs where the log level can be changed via a steering 
     *  parameter.
     *  
     *  @see logstream::logscope::setLevel(const std::string levelName )
     */
    template <class T>
    void addLevelName() {

      _map[ T::name() ] = T::level ;
    }

    // interface for friend classes: scope

  protected:

    /** Set the current level - user need to use a streamlog::logscope object 
     *  to do this.
     */
    void setLevel( unsigned level ) { _level = level ; } 

    /** Set the current level through its name - only level previously made known to
     *  the stream through addLevelName will have an effect.
     */
    unsigned setLevel( const std::string& levelName )  ; 

    /** Returns the prefix */
    prefix_base* prefix() { return _prefix ; }

    /** used internally by write<T> */
    template<class T>
    bool check_level() {
      
      if( T::level >= _level ){
	_active = true ;
	_prefix->_levelName = T::name() ;
      }
      return _active ;
    }


  private:

    std::ostream* _os = &std::cout ; // wrapper for actual ostream
    unsigned _level {};   // current log level 
    bool _active {};      // boolean helper 
    prefix_base* _prefix= nullptr ;  // prefix formatter
    LevelMap _map {};         // string map of level names
    
  } ;

  extern thread_local logstream out ;

}
#endif
