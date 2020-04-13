
// -- streamlogplus interface headers
#include <streamlogplus/config.h>
#include <streamlogplus/loglevels.h>
#include <streamlogplus/logger.h>

namespace streamlogplus {
  
  /** @name Global logger
   */
  ///{@
  inline void configure( const std::string &lname, const std::string &lvl, std::vector<sink_pool::sink_ptr> sinks ) {
    auto &logger = logger::global() ;
    logger.set_name( lname ) ;
    logger.set_level( lvl ) ;
    logger.set_sinks( std::move(sinks) ) ;
  }
  
  inline void set_name( const std::string &lname ) {
    logger::global().set_name( lname ) ;
  }
  
  inline void set_level( const std::string &lvl_str ) {
    logger::global().set_level( lvl_str ) ;
  }
  
  template <class MLEVEL>
  inline void set_level() {
    logger::global().set_level<MLEVEL>() ;
  }
  
  inline void set_formatter( formatter_function fmtfunc ) {
    logger::global().set_formatter( std::move(fmtfunc) ) ;
  }
  
  template <typename ...Args>
  inline void debug(const char *format, const Args& ...args ) { logger::global().debug( format, args... ) ; }
  template <typename ...Args>
  inline void debug0(const char *format, const Args& ...args ) { logger::global().debug0( format, args... ) ; }
  template <typename ...Args>
  inline void debug1(const char *format, const Args& ...args ) { logger::global().debug1( format, args... ) ; }
  template <typename ...Args>
  inline void debug2(const char *format, const Args& ...args ) { logger::global().debug2( format, args... ) ; }
  template <typename ...Args>
  inline void debug3(const char *format, const Args& ...args ) { logger::global().debug3( format, args... ) ; }
  template <typename ...Args>
  inline void debug4(const char *format, const Args& ...args ) { logger::global().debug4( format, args... ) ; }
  template <typename ...Args>
  inline void debug5(const char *format, const Args& ...args ) { logger::global().debug5( format, args... ) ; }
  template <typename ...Args>
  inline void debug6(const char *format, const Args& ...args ) { logger::global().debug6( format, args... ) ; }
  template <typename ...Args>
  inline void debug7(const char *format, const Args& ...args ) { logger::global().debug7( format, args... ) ; }
  template <typename ...Args>
  inline void debug8(const char *format, const Args& ...args ) { logger::global().debug8( format, args... ) ; }
  template <typename ...Args>
  inline void debug9(const char *format, const Args& ...args ) { logger::global().debug9( format, args... ) ; }
  
  template <typename ...Args>
  inline void message(const char *format, const Args& ...args ) { logger::global().message( format, args... ) ; }
  template <typename ...Args>
  inline void message0(const char *format, const Args& ...args ) { logger::global().message0( format, args... ) ; }
  template <typename ...Args>
  inline void message1(const char *format, const Args& ...args ) { logger::global().message1( format, args... ) ; }
  template <typename ...Args>
  inline void message2(const char *format, const Args& ...args ) { logger::global().message2( format, args... ) ; }
  template <typename ...Args>
  inline void message3(const char *format, const Args& ...args ) { logger::global().message3( format, args... ) ; }
  template <typename ...Args>
  inline void message4(const char *format, const Args& ...args ) { logger::global().message4( format, args... ) ; }
  template <typename ...Args>
  inline void message5(const char *format, const Args& ...args ) { logger::global().message5( format, args... ) ; }
  template <typename ...Args>
  inline void message6(const char *format, const Args& ...args ) { logger::global().message6( format, args... ) ; }
  template <typename ...Args>
  inline void message7(const char *format, const Args& ...args ) { logger::global().message7( format, args... ) ; }
  template <typename ...Args>
  inline void message8(const char *format, const Args& ...args ) { logger::global().message8( format, args... ) ; }
  template <typename ...Args>
  inline void message9(const char *format, const Args& ...args ) { logger::global().message9( format, args... ) ; }
  
  template <typename ...Args>
  inline void warning(const char *format, const Args& ...args ) { logger::global().warning( format, args... ) ; }
  template <typename ...Args>
  inline void warning0(const char *format, const Args& ...args ) { logger::global().warning0( format, args... ) ; }
  template <typename ...Args>
  inline void warning1(const char *format, const Args& ...args ) { logger::global().warning1( format, args... ) ; }
  template <typename ...Args>
  inline void warning2(const char *format, const Args& ...args ) { logger::global().warning2( format, args... ) ; }
  template <typename ...Args>
  inline void warning3(const char *format, const Args& ...args ) { logger::global().warning3( format, args... ) ; }
  template <typename ...Args>
  inline void warning4(const char *format, const Args& ...args ) { logger::global().warning4( format, args... ) ; }
  template <typename ...Args>
  inline void warning5(const char *format, const Args& ...args ) { logger::global().warning5( format, args... ) ; }
  template <typename ...Args>
  inline void warning6(const char *format, const Args& ...args ) { logger::global().warning6( format, args... ) ; }
  template <typename ...Args>
  inline void warning7(const char *format, const Args& ...args ) { logger::global().warning7( format, args... ) ; }
  template <typename ...Args>
  inline void warning8(const char *format, const Args& ...args ) { logger::global().warning8( format, args... ) ; }
  template <typename ...Args>
  inline void warning9(const char *format, const Args& ...args ) { logger::global().warning9( format, args... ) ; }

  template <typename ...Args>
  inline void error(const char *format, const Args& ...args ) { logger::global().error( format, args... ) ; }
  template <typename ...Args>
  inline void error0(const char *format, const Args& ...args ) { logger::global().error0( format, args... ) ; }
  template <typename ...Args>
  inline void error1(const char *format, const Args& ...args ) { logger::global().error1( format, args... ) ; }
  template <typename ...Args>
  inline void error2(const char *format, const Args& ...args ) { logger::global().error2( format, args... ) ; }
  template <typename ...Args>
  inline void error3(const char *format, const Args& ...args ) { logger::global().error3( format, args... ) ; }
  template <typename ...Args>
  inline void error4(const char *format, const Args& ...args ) { logger::global().error4( format, args... ) ; }
  template <typename ...Args>
  inline void error5(const char *format, const Args& ...args ) { logger::global().error5( format, args... ) ; }
  template <typename ...Args>
  inline void error6(const char *format, const Args& ...args ) { logger::global().error6( format, args... ) ; }
  template <typename ...Args>
  inline void error7(const char *format, const Args& ...args ) { logger::global().error7( format, args... ) ; }
  template <typename ...Args>
  inline void error8(const char *format, const Args& ...args ) { logger::global().error8( format, args... ) ; }
  template <typename ...Args>
  inline void error9(const char *format, const Args& ...args ) { logger::global().error9( format, args... ) ; }
  ///@}
}