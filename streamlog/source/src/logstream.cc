#include "streamlog/logstream.h"

#include "streamlog/logbuffer.h"
#include "streamlog/prefix.h"

namespace streamlog{
  
  logstream::logstream() : 
    _ns( new nullstream ) , 
    _os(0) , 
    _level(0) ,
    _active(false) , 
    _lb(0),
    _prefix( new streamlog::prefix) {
    
  } 

  logstream::~logstream() {
    
    if( _ns ){ 
        delete _ns ;
        _ns = NULL ;
    }
    
    if( _os ){ 
      delete _os ;
      _os = NULL ;
    }
    
    if( _lb ){
      delete _lb ;
      _lb = NULL ;
    }
    
    if( _prefix ){
      delete _prefix ;
      _prefix = NULL ; 
    }
  }
  
  void logstream::init( std::ostream& os , const std::string &name ) {
    
    static bool first=true ;
    
    if( first && os ) {
      
      //      _name = name ;      
      
      // create a new log buffer and attach this to a wrapper to the given ostream  

      _lb = new logbuffer( os.rdbuf() , this ) ;
      
      _os = new std::ostream( _lb ) ;
      
      //attach also the original stream to the logger...
      //os.rdbuf( _lb ) ; // this needs some work 
      // FIXME : this needs to go to the c'tor !!!!
     
      _prefix->_name = name ;

      first = false ;
    }
    
    else if( !os) {
      std::cerr << "ERROR: logstream::init() invalid ostream given " << std::endl ;      
    }
  }

  unsigned logstream::setLevel( const std::string& levelName ) {

    unsigned l = _level ;
    LevelMap::iterator it = _map.find( levelName ) ;
    if( it != _map.end() ) {
      _level = it->second ;
    }
    return l ;
  } 


  printthread logstream::operator()() { 
    
    if( _active && _os ) {
      
      _active = false ;
      
      return printthread{(_prefix)(),_os} ;
    }
    else
      return printthread{} ;
    
  }

  /** global instance of logstream */
  logstream out ;
}
