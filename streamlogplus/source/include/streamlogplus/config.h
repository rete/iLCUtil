
#pragma once

namespace streamlogplus {

  /// config struct
  /// Handles the configuration constants of streamlogplus 
  struct config {
#ifndef STREAMLOG_LEVEL
#ifndef NDEBUG
    /// The minimum verbosity level (compile time)
    static constexpr unsigned int min_level = 0 ;
#else
    static constexpr unsigned int min_level = 1 ;
#endif
#else
    static constexpr unsigned int min_level = STREAMLOG_LEVEL ;
#endif
    /// The maximum verbosity level (TODO: needed ?)
    static constexpr unsigned int max_level = 0xFFFFFFFF ;
    /// Whether the debug level is active
    static constexpr bool debug_active      = (min_level < 1) ;
    /// Whether the message level is active
    static constexpr bool message_active    = (min_level < 2) ;
    /// Whether the warning level is active
    static constexpr bool warning_active    = (min_level < 3) ;
    /// Whether the error level is active
    static constexpr bool error_active      = (min_level < 4) ;

    /// The base verbosity level for debug
    static constexpr unsigned int debug_base_level   = 0 ;
    /// The base verbosity level for message
    static constexpr unsigned int message_base_level = 100 ;
    /// The base verbosity level for warning
    static constexpr unsigned int warning_base_level = 200 ;
    /// The base verbosity level for error
    static constexpr unsigned int error_base_level   = 300 ;
  };
  
}