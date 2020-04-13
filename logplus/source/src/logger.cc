
#include <logplus/logger.h>

namespace logplus {
  
  logger __globallogger__ ;

  logger::logger( const std::string &ln ) : 
    _name(ln) {
    /* nop */
  }
  
  //--------------------------------------------------------------------------
  
  logger::logger( const std::string &ln, const logger &other ) :
    _name(ln),
    _level(other._level),
    _fmtfunc(other._fmtfunc) {
    share_sinks( other ) ;
  }
  
  //--------------------------------------------------------------------------
  
  logger &logger::global() {
    return __globallogger__ ;
  }
  
  //--------------------------------------------------------------------------
  
  unsigned int logger::level() const {
    std::shared_lock lock(_mutex) ;
    return _level ;
  }
  
  //--------------------------------------------------------------------------
  
  std::string logger::level_string() const {
    std::shared_lock lock(_mutex) ;
    return levels::get_string_from_level( _level ) ;
  }
  
  //--------------------------------------------------------------------------
  
  std::string logger::name() const {
    std::shared_lock lock(_mutex) ;
    return _name ;
  }
  
  //--------------------------------------------------------------------------
  
  void logger::set_name( const std::string &n ) {
    std::unique_lock lock(_mutex) ;
    _name = n ;
  }
  
  //--------------------------------------------------------------------------
  
  void logger::set_level( const std::string &lvl_str ) {
    std::unique_lock lock(_mutex) ;
    _level = levels::get_level_from_string( lvl_str ) ;
  }
  
  //--------------------------------------------------------------------------
  
  void logger::set_formatter( formatter_function fmt_func ) {
    std::unique_lock lock(_mutex) ;
    _fmtfunc = std::move( fmt_func ) ;
  }
  
  //--------------------------------------------------------------------------
  
  void logger::set_sinks( std::vector<sink_pool::sink_ptr> sinks ) {
    std::unique_lock lock(_mutex) ;
    _sinkpool.add_sinks( std::move( sinks ) ) ;
  }
  
  //--------------------------------------------------------------------------
  
  void logger::add_sink( sink_pool::sink_ptr s ) {
    std::unique_lock lock(_mutex) ;
    _sinkpool.push_back( s ) ;
  }
  
  //--------------------------------------------------------------------------
  
  void logger::share_sinks( const logger &other ) {
    std::unique_lock lock(_mutex) ;
    _sinkpool = other._sinkpool.create_shared_pool() ;
  }
  
}