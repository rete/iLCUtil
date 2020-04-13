
#include <string>
#include <mutex>
#include <shared_mutex>
#include <iostream>
#include <fstream>
#include <thread>
#include <vector>
#include <unordered_map>

#include <logplus/loglevels.h>

namespace logplus {
  
  class sink {
  public:
    sink() = default ;
    virtual ~sink() = default ;
    virtual void push( const std::string &message ) = 0 ;
  };
  
  class sink_pool {
  public:
    using sink_ptr = std::shared_ptr<sink> ;
    
    sink_pool() = default ;
    sink_pool( sink_pool&& ) = default ;
    sink_pool& operator=( sink_pool&& ) = default ;
    sink_pool( const sink_pool& ) = default ;
    sink_pool& operator=( const sink_pool& ) = default ;
    
    /// Constructor with sinks
    sink_pool( std::vector<sink_ptr> sinks ) ;
    
    /// Add a shared sink to the pool
    void push_back( sink_ptr s ) ;
    
    /// Add a new sink by constructing it
    template <typename SINK, typename ...Args>
    void add_sink( Args ...args ) {
      _sinks.push_back( std::make_shared<SINK>(args...) ) ;
    }
    
    /// Add a list of sinks
    void add_sinks( std::vector<sink_ptr> sinks ) {
      _sinks.insert( _sinks.end(), sinks.begin(), sinks.end() ) ;
    }
    
    /// Remove all sinks
    void clear() ;
    
    /// Push the message into the sinks
    void push_message( std::string message ) const ;
    
    /// Create a new pool sharing the existing sinks.
    /// Newly added sinks won't be shared in the new pool
    sink_pool create_shared_pool() const ;
    
  private:
    std::vector<sink_ptr>    _sinks {} ;
  };
  
  class console_sink : public sink {
  public:
    console_sink() = default ;
    static std::shared_ptr<sink> make_shared() ;
    void push( const std::string &message ) override ;
  };
  
  class file_sink_st : public sink {
  public:
    file_sink_st( std::string &fname, std::ios_base::openmode mode = std::ios_base::out ) ;
    virtual ~file_sink_st() ;
    static std::shared_ptr<sink> make_shared( std::string &fname, std::ios_base::openmode mode = std::ios_base::out ) ;
    virtual void push( const std::string &message ) override ;
  private:
    std::ofstream    _stream {} ;
  };
  
  class file_sink_mt : public file_sink_st {
  public:
    file_sink_mt( std::string &fname, std::ios_base::openmode mode = std::ios_base::out ) ;
    static std::shared_ptr<sink> make_shared( std::string &fname, std::ios_base::openmode mode = std::ios_base::out ) ;
    void push( const std::string &message ) override ;
  private:
    std::mutex     _mutex {} ;
  };
  
  class thread_file_sink : public sink {
  public:
    thread_file_sink( std::string &fname, std::ios_base::openmode mode = std::ios_base::out ) ;
    ~thread_file_sink() ;
    static std::shared_ptr<sink> make_shared( std::string &fname, std::ios_base::openmode mode = std::ios_base::out ) ;
    virtual void push( const std::string &message ) override ;    
  private:
    std::ofstream &find_stream() ;
    std::ofstream open( std::thread::id id ) const ;
  private:
    std::shared_mutex    _mutex {} ;
    /// The map of output files, mapped by thread id
    std::unordered_map<std::thread::id, std::ofstream>   _streams {} ;
    /// The log file name
    std::string             _fname {} ;
    /// The log file open mode
    std::ios_base::openmode _openmode {} ;
  };
  
}