
// -- std headers 
#include <string>
#include <mutex>

// -- streamlogplus headers
#include <logplus/loglevels.h>
#include <logplus/formatter.h>
#include <logplus/sink.h>

namespace logplus {
  
  /// logger class. 
  /// A logger consist of a name and a verbosity level being adjustable.
  /// Different methods are available to choose the verbosity level with
  /// which the user wants to use for a message. The message formatting is
  /// processed by the fmt library in nice python style.
  /// The final pool for message is the so-called sink pool which can also
  /// be adjusted at runtime (cout, file, user defined)
  /// @see sink
  /// @see sink_pool 
  class logger {
  public:
    /**
     *  @name Special methods
     */
    ///{@
    /// Default constructor
    logger() = default ;
    
    /// Default destructor
    ~logger() = default ;
    
    /// Constructor with logger name
    logger( const std::string &ln ) ;
    
    /// Constructor with logger name and other logger 
    /// from which to share the sink pool
    logger( const std::string &ln, const logger &other ) ;
    ///@}
    
    /**
     *  @name Global logger
     */
    ///{@
    static logger &global() ;
    ///@}
    
    /**
     *  @name Getters
     */
    ///{@
    /// Get the log level
    unsigned int level() const ;
    
    /// Get the log level as string
    std::string level_string() const ;
    
    /// Get the logger name
    std::string name() const ;
    ///@}
    
    /** @name Logging functions
     */
    ///@{    
    /// Log a message with a specific log level
    /// The log level is formatted only if the specified level 
    /// is higher than the one of the logger
    template <class MLEVEL, typename ...Args>
    void log( [[maybe_unused]] const char *format, [[maybe_unused]] const Args& ...args ) const {
      if constexpr ( MLEVEL::active ) {
        std::shared_lock lock(_mutex) ;
        if( _level <= MLEVEL::level ) {
          auto message = create_message( _name, MLEVEL::name, fmt::format(format, args...) ) ;
          _sinkpool.push_message( _fmtfunc( message ) ) ;
        }
      }
    }
    
    template <typename ...Args>
    void debug( const char *format, const Args& ...args ) const { log<levels::DEBUG>( format, args... ) ; }
    template <typename ...Args>
    void debug0( const char *format, const Args& ...args ) const { log<levels::DEBUG0>( format, args... ) ; }
    template <typename ...Args>
    void debug1( const char *format, const Args& ...args ) const { log<levels::DEBUG1>( format, args... ) ; }
    template <typename ...Args>
    void debug2( const char *format, const Args& ...args ) const { log<levels::DEBUG2>( format, args... ) ; }
    template <typename ...Args>
    void debug3( const char *format, const Args& ...args ) const { log<levels::DEBUG3>( format, args... ) ; }
    template <typename ...Args>
    void debug4( const char *format, const Args& ...args ) const { log<levels::DEBUG4>( format, args... ) ; }
    template <typename ...Args>
    void debug5( const char *format, const Args& ...args ) const { log<levels::DEBUG5>( format, args... ) ; }
    template <typename ...Args>
    void debug6( const char *format, const Args& ...args ) const { log<levels::DEBUG6>( format, args... ) ; }
    template <typename ...Args>
    void debug7( const char *format, const Args& ...args ) const { log<levels::DEBUG7>( format, args... ) ; }
    template <typename ...Args>
    void debug8( const char *format, const Args& ...args ) const { log<levels::DEBUG8>( format, args... ) ; }
    template <typename ...Args>
    void debug9( const char *format, const Args& ...args ) const { log<levels::DEBUG9>( format, args... ) ; }
    
    template <typename ...Args>
    void message( const char *format, const Args& ...args ) const { log<levels::MESSAGE>( format, args... ) ; }
    template <typename ...Args>
    void message0( const char *format, const Args& ...args ) const { log<levels::MESSAGE0>( format, args... ) ; }
    template <typename ...Args>
    void message1( const char *format, const Args& ...args ) const { log<levels::MESSAGE1>( format, args... ) ; }
    template <typename ...Args>
    void message2( const char *format, const Args& ...args ) const { log<levels::MESSAGE2>( format, args... ) ; }
    template <typename ...Args>
    void message3( const char *format, const Args& ...args ) const { log<levels::MESSAGE3>( format, args... ) ; }
    template <typename ...Args>
    void message4( const char *format, const Args& ...args ) const { log<levels::MESSAGE4>( format, args... ) ; }
    template <typename ...Args>
    void message5( const char *format, const Args& ...args ) const { log<levels::MESSAGE5>( format, args... ) ; }
    template <typename ...Args>
    void message6( const char *format, const Args& ...args ) const { log<levels::MESSAGE6>( format, args... ) ; }
    template <typename ...Args>
    void message7( const char *format, const Args& ...args ) const { log<levels::MESSAGE7>( format, args... ) ; }
    template <typename ...Args>
    void message8( const char *format, const Args& ...args ) const { log<levels::MESSAGE8>( format, args... ) ; }
    template <typename ...Args>
    void message9( const char *format, const Args& ...args ) const { log<levels::MESSAGE9>( format, args... ) ; }
    
    template <typename ...Args>
    void warning( const char *format, const Args& ...args ) const { log<levels::WARNING>( format, args... ) ; }
    template <typename ...Args>
    void warning0( const char *format, const Args& ...args ) const { log<levels::WARNING0>( format, args... ) ; }
    template <typename ...Args>
    void warning1( const char *format, const Args& ...args ) const { log<levels::WARNING1>( format, args... ) ; }
    template <typename ...Args>
    void warning2( const char *format, const Args& ...args ) const { log<levels::WARNING2>( format, args... ) ; }
    template <typename ...Args>
    void warning3( const char *format, const Args& ...args ) const { log<levels::WARNING3>( format, args... ) ; }
    template <typename ...Args>
    void warning4( const char *format, const Args& ...args ) const { log<levels::WARNING4>( format, args... ) ; }
    template <typename ...Args>
    void warning5( const char *format, const Args& ...args ) const { log<levels::WARNING5>( format, args... ) ; }
    template <typename ...Args>
    void warning6( const char *format, const Args& ...args ) const { log<levels::WARNING6>( format, args... ) ; }
    template <typename ...Args>
    void warning7( const char *format, const Args& ...args ) const { log<levels::WARNING7>( format, args... ) ; }
    template <typename ...Args>
    void warning8( const char *format, const Args& ...args ) const { log<levels::WARNING8>( format, args... ) ; }
    template <typename ...Args>
    void warning9( const char *format, const Args& ...args ) const { log<levels::WARNING9>( format, args... ) ; }
    
    template <typename ...Args>
    void error( const char *format, const Args& ...args ) const { log<levels::ERROR>( format, args... ) ; }
    template <typename ...Args>
    void error0( const char *format, const Args& ...args ) const { log<levels::ERROR0>( format, args... ) ; }
    template <typename ...Args>
    void error1( const char *format, const Args& ...args ) const { log<levels::ERROR1>( format, args... ) ; }
    template <typename ...Args>
    void error2( const char *format, const Args& ...args ) const { log<levels::ERROR2>( format, args... ) ; }
    template <typename ...Args>
    void error3( const char *format, const Args& ...args ) const { log<levels::ERROR3>( format, args... ) ; }
    template <typename ...Args>
    void error4( const char *format, const Args& ...args ) const { log<levels::ERROR4>( format, args... ) ; }
    template <typename ...Args>
    void error5( const char *format, const Args& ...args ) const { log<levels::ERROR5>( format, args... ) ; }
    template <typename ...Args>
    void error6( const char *format, const Args& ...args ) const { log<levels::ERROR6>( format, args... ) ; }
    template <typename ...Args>
    void error7( const char *format, const Args& ...args ) const { log<levels::ERROR7>( format, args... ) ; }
    template <typename ...Args>
    void error8( const char *format, const Args& ...args ) const { log<levels::ERROR8>( format, args... ) ; }
    template <typename ...Args>
    void error9( const char *format, const Args& ...args ) const { log<levels::ERROR9>( format, args... ) ; }
    ///@}
    
    /** @name Modifiers
     */
    ///{@
    /// Set the logger name
    void set_name( const std::string &n ) ;
    
    /// Set the log level
    template <class MLEVEL>
    inline void set_level() {
      std::unique_lock lock(_mutex) ;
      _level = MLEVEL::level ;
    }
    
    /// Set the log level (from string)
    void set_level( const std::string &lvl_str ) ;
    
    /// Set the formatter function
    void set_formatter( formatter_function fmt_func ) ;
    
    /// Set the sinks (replace)
    void set_sinks( std::vector<sink_pool::sink_ptr> sinks ) ;
    
    /// Add a sink to the pool
    void add_sink( sink_pool::sink_ptr s ) ;
    
    /// Replace the current sink pool by using the same as an other logger
    void share_sinks( const logger &other ) ;
    ///@}
    
  private:
    /// Synchronization mutex
    mutable std::shared_mutex       _mutex {} ;
    /// The logger name
    std::string                     _name {"default"} ;
    /// The logger log level
    unsigned int                    _level {levels::MESSAGE::level} ;
    /// The message formatter function
    formatter_function              _fmtfunc { builtin::simple_pattern() } ;
    /// The sink pool
    sink_pool                       _sinkpool { {console_sink::make_shared()} } ;
  };
  
}