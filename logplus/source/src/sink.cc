
#include <logplus/sink.h>

#include <filesystem>
#include <stdexcept>
#include <sstream>

namespace logplus {
  
  std::mutex __mcout__ {} ;
  
  sink_pool::sink_pool( std::vector<sink_ptr> sinks ) :
    _sinks(std::move(sinks)) {
    /* nop */
  }
  
  void sink_pool::push_message( std::string message ) const {
    for( auto s : _sinks ) {
      s->push( message ) ;
    }
  }
  
  void sink_pool::push_back( sink_pool::sink_ptr s ) {
    _sinks.push_back( s ) ;
  }
  
  void sink_pool::clear() {
    _sinks.clear() ;
  }
  
  sink_pool sink_pool::create_shared_pool() const {
    return sink_pool( _sinks ) ;
  }
  
  std::shared_ptr<sink> console_sink::make_shared() { 
    return std::make_shared<console_sink>() ; 
  }
  
  void console_sink::push( const std::string &message ) {
    std::lock_guard lock(__mcout__) ;
    std::cout << message << std::endl ;
  }
  
  file_sink_st::file_sink_st( std::string &fname, std::ios_base::openmode mode ) : 
    _stream( fname, mode ) {
    if( not _stream ) {
      throw std::runtime_error( "Couldn't open log file '" + fname + "'" ) ;
    }
  }
  
  file_sink_st::~file_sink_st() {
    _stream.close() ;
  }
  
  std::shared_ptr<sink> file_sink_st::make_shared( std::string &fname, std::ios_base::openmode mode ) { 
    return std::make_shared<file_sink_st>( fname, mode ) ; 
  }
  
  void file_sink_st::push( const std::string &message ) {
    _stream << message << std::endl ;
  }
  
  file_sink_mt::file_sink_mt( std::string &fname, std::ios_base::openmode mode ) :
    file_sink_st(fname, mode) {
    /* nop */
  }
  
  std::shared_ptr<sink> file_sink_mt::make_shared( std::string &fname, std::ios_base::openmode mode ) { 
    return std::make_shared<file_sink_mt>( fname, mode ) ; 
  }
  
  void file_sink_mt::push( const std::string &message ) {
    std::lock_guard lock(_mutex) ;
    file_sink_st::push( message ) ;
  }
  
  
  thread_file_sink::thread_file_sink( std::string &fname, std::ios_base::openmode mode ) :
    _fname(fname),
    _openmode(mode) {
    std::filesystem::path fpath = _fname ;
    if( not fpath.has_extension() ) {
      _fname = fpath.replace_extension(".log").string() ;
    }
  }
  
  thread_file_sink::~thread_file_sink() {
    for( auto &f : _streams ) {
      f.second.close() ;
    }
    _streams.clear() ;
  }
  
  std::shared_ptr<sink> thread_file_sink::make_shared( std::string &fname, std::ios_base::openmode mode ) { 
    return std::make_shared<thread_file_sink>( fname, mode ) ; 
  }
  
  void thread_file_sink::push( const std::string &message ) {
    auto &stream = find_stream() ;
    stream << message << std::endl ;
  }
  
  std::ofstream &thread_file_sink::find_stream() {
    auto thread_id = std::this_thread::get_id() ;
    {
      std::shared_lock lock(_mutex) ;
      auto iter = _streams.find( thread_id ) ;
      if ( _streams.end() != iter ) {
        return iter->second ;
      }      
    }
    std::unique_lock lock(_mutex) ;
    return _streams.insert( {thread_id, open(thread_id) } ).first->second ;
  }
  
  std::ofstream thread_file_sink::open( std::thread::id id ) const {
    std::filesystem::path fpath = _fname ;
    std::stringstream ss ; ss << "." << id << fpath.extension().string() ;
    fpath.replace_extension( ss.str() ) ;
    std::ofstream fs( fpath.string(), _openmode ) ;
    if ( not fs.is_open() ) {
      throw std::runtime_error( "Couldn't open log file '" + fpath.string() + "'" ) ;
    }
    fs << "Opened new log file '" << fpath.string() << "' for thread id " << id << std::endl ;
    return fs ;
  }
  
}
