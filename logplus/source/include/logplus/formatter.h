
// -- std headers
#include <string>
#include <thread>
#include <ctime>
#include <functional>

// -- fmt headers
#include <fmt/format.h>
#include <fmt/chrono.h>
#include <fmt/ostream.h>

namespace logplus {
  
  /// message_data struct
  /// A simple structure handling data about a message being logged
  /// Can be easily extended by developpers if needed
  struct message_data {
    /// The logger name
    std::string                     _logger {} ;
    /// The verbosity level
    std::string                     _level {} ;
    /// The message
    std::string                     _message {} ;
    /// The time at which the message was logged
    std::time_t                     _time {} ;
    /// The thread id
    std::thread::id                 _threadId {} ;
  };
  
  /// Create a message structure out of basic informations
  inline message_data create_message( std::string logger, std::string level, std::string message ) {
    return { std::move(logger), std::move(level), std::move(message), std::time(nullptr), std::this_thread::get_id() } ;
  }
  
  using formatter_function = std::function<std::string(const message_data &)> ;
  
  namespace builtin {
    /// A simple formatter pattern with only logger name, log level and message
    [[maybe_unused]] static formatter_function simple_pattern() {
      return [](const message_data &data) {
        return fmt::format( "[{} \"{}\"] {}", data._logger, data._level, data._message ) ;
      };
    }
    
    /// A formatter pattern with logger name, log level, time and message
    [[maybe_unused]] static formatter_function time_pattern() {
      return [](const message_data &data) {
        return fmt::format( "[{} \"{}\"] {:%T} - {}", data._logger, data._level, *std::localtime(&data._time), data._message ) ;
      };  
    }
    
    /// A formatter pattern with logger name, log level, thread id and message
    [[maybe_unused]] static formatter_function thread_pattern() {
      return [](const message_data &data) {
        return fmt::format( "[{} \"{}\" #{}] - {}", data._logger, data._level, data._threadId, data._message ) ;
      };
    }
    
    /// A formatter pattern with all info from the message_data structure 
    [[maybe_unused]] static formatter_function full_pattern() {
      return [](const message_data &data) {
        return fmt::format( "[{} \"{}\" #{}] {:%T} - {}", data._logger, data._level, data._threadId, *std::localtime(&data._time), data._message ) ;
      };  
    }    
  }

}