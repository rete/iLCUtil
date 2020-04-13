#pragma once

// -- std headers
#include <stdexcept>

// -- streamlogplus headers
#include <logplus/config.h>

namespace logplus {
    
  /// base_verbosity struct
  /// The base definition for verbosity level 
  template <unsigned LEVEL, bool ACTIVE>
  struct base_verbosity {
    static constexpr unsigned int level = LEVEL ; 
    static constexpr bool active = ACTIVE ;
  };
  
#define DECLARE_VERBOSITY_LEVEL( NAME, LEVEL, ACTIVE, STRING ) \
  struct verbosity_##NAME : public base_verbosity<LEVEL, ACTIVE> { \
    static constexpr const char *name = STRING ; \
  }; \
  using NAME = verbosity_##NAME ;

#define GET_LEVEL_FROM_STR( NAME, LEVEL, ACTIVE, STRING ) \
  if( str == STRING ) return LEVEL ;
  
#define GET_STR_FROM_LEVEL( NAME, LEVEL, ACTIVE, STRING ) \
  if( lvl == LEVEL ) return STRING ;

#define VERBOSITY_TABLE(d) \
  d( DEBUG,    config::debug_base_level,     config::debug_active,   "DEBUG" ) \
  d( DEBUG0,   config::debug_base_level,     config::debug_active,   "DEBUG0" ) \
  d( DEBUG1,   config::debug_base_level+1,   config::debug_active,   "DEBUG1" ) \
  d( DEBUG2,   config::debug_base_level+2,   config::debug_active,   "DEBUG2" ) \
  d( DEBUG3,   config::debug_base_level+3,   config::debug_active,   "DEBUG3" ) \
  d( DEBUG4,   config::debug_base_level+4,   config::debug_active,   "DEBUG4" ) \
  d( DEBUG5,   config::debug_base_level+5,   config::debug_active,   "DEBUG5" ) \
  d( DEBUG6,   config::debug_base_level+6,   config::debug_active,   "DEBUG6" ) \
  d( DEBUG7,   config::debug_base_level+7,   config::debug_active,   "DEBUG7" ) \
  d( DEBUG8,   config::debug_base_level+8,   config::debug_active,   "DEBUG8" ) \
  d( DEBUG9,   config::debug_base_level+9,   config::debug_active,   "DEBUG9" ) \
  d( MESSAGE,  config::message_base_level,   config::message_active, "MESSAGE" ) \
  d( MESSAGE0, config::message_base_level,   config::message_active, "MESSAGE0" ) \
  d( MESSAGE1, config::message_base_level+1, config::message_active, "MESSAGE1" ) \
  d( MESSAGE2, config::message_base_level+2, config::message_active, "MESSAGE2" ) \
  d( MESSAGE3, config::message_base_level+3, config::message_active, "MESSAGE3" ) \
  d( MESSAGE4, config::message_base_level+4, config::message_active, "MESSAGE4" ) \
  d( MESSAGE5, config::message_base_level+5, config::message_active, "MESSAGE5" ) \
  d( MESSAGE6, config::message_base_level+6, config::message_active, "MESSAGE6" ) \
  d( MESSAGE7, config::message_base_level+7, config::message_active, "MESSAGE7" ) \
  d( MESSAGE8, config::message_base_level+8, config::message_active, "MESSAGE8" ) \
  d( MESSAGE9, config::message_base_level+9, config::message_active, "MESSAGE9" ) \
  d( WARNING,  config::warning_base_level,   config::warning_active, "WARNING" ) \
  d( WARNING0, config::warning_base_level,   config::warning_active, "WARNING0" ) \
  d( WARNING1, config::warning_base_level+1, config::warning_active, "WARNING1" ) \
  d( WARNING2, config::warning_base_level+2, config::warning_active, "WARNING2" ) \
  d( WARNING3, config::warning_base_level+3, config::warning_active, "WARNING3" ) \
  d( WARNING4, config::warning_base_level+4, config::warning_active, "WARNING4" ) \
  d( WARNING5, config::warning_base_level+5, config::warning_active, "WARNING5" ) \
  d( WARNING6, config::warning_base_level+6, config::warning_active, "WARNING6" ) \
  d( WARNING7, config::warning_base_level+7, config::warning_active, "WARNING7" ) \
  d( WARNING8, config::warning_base_level+8, config::warning_active, "WARNING8" ) \
  d( WARNING9, config::warning_base_level+9, config::warning_active, "WARNING9" ) \
  d( ERROR,    config::error_base_level,     config::error_active,   "ERROR" ) \
  d( ERROR0,   config::error_base_level,     config::error_active,   "ERROR0" ) \
  d( ERROR1,   config::error_base_level+1,   config::error_active,   "ERROR1" ) \
  d( ERROR2,   config::error_base_level+2,   config::error_active,   "ERROR2" ) \
  d( ERROR3,   config::error_base_level+3,   config::error_active,   "ERROR3" ) \
  d( ERROR4,   config::error_base_level+4,   config::error_active,   "ERROR4" ) \
  d( ERROR5,   config::error_base_level+5,   config::error_active,   "ERROR5" ) \
  d( ERROR6,   config::error_base_level+6,   config::error_active,   "ERROR6" ) \
  d( ERROR7,   config::error_base_level+7,   config::error_active,   "ERROR7" ) \
  d( ERROR8,   config::error_base_level+8,   config::error_active,   "ERROR8" ) \
  d( ERROR9,   config::error_base_level+9,   config::error_active,   "ERROR9" )  
  
  namespace levels {
    
    VERBOSITY_TABLE( DECLARE_VERBOSITY_LEVEL )
    
    /// Helper function to get the log level from the input string 
    /// Throws if the string doesn't match
    inline unsigned int get_level_from_string( const std::string &str ) {
      VERBOSITY_TABLE( GET_LEVEL_FROM_STR )
      throw std::runtime_error( "Unknown verbosity level " + str ) ;
    }
    
    /// Helper function to get the log level as string from the input log level 
    /// Throws if the log level doesn't match
    inline std::string get_string_from_level( unsigned int lvl ) {
      VERBOSITY_TABLE( GET_STR_FROM_LEVEL )
      throw std::runtime_error( "Unknown verbosity level" ) ;
    }
  }
  
#undef DECLARE_VERBOSITY_LEVEL
#undef GET_LEVEL_FROM_STR
#undef GET_STR_FROM_LEVEL
#undef VERBOSITY_TABLE
}
