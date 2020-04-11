
#include <streamlogplus/streamlogplus.h>

using namespace streamlogplus::levels ;
using namespace streamlogplus ;

void printout_test() {
  message( "This message should normally not be interleaved by messages from other threads" ) ;
  warning( "This message should normally not be interleaved by messages from other threads" ) ;
  error( "This message should normally not be interleaved by messages from other threads" ) ;
}

int main() {
  
  message( "Hello world!" ) ;
  warning( "Hello world... ouch" ) ;
  error( "Hello world... oh nooooooooooo!" ) ;

  // create a logger
  logger l( "test" ) ;
  l.set_level( "MESSAGE" ) ;
  
  l.debug( "This is a debug message" ) ;
  l.message( "This is a message message" ) ;
  l.warning( "This is a warning message" ) ;
  l.error( "This is an error message" ) ;
  
  l.debug( "If debug is OFF, {} won't print out this message", "supercat" ) ;
  l.message( "The answer is {}", 42 ) ;
  l.warning( "Warning: {} is winning !", "superman" ) ;
  l.error( "{} / {} = {}", 40, 2, 20 ) ;
  
  l.set_level( "WARNING" ) ;
  l.message( "This won't be printed" ) ;
  
  // set a pattern where the thread id is printed
  std::vector<std::thread> threads(8) ;
  set_formatter( builtin::thread_pattern() ) ;
  
  // create 8 threads and run the printout test
  for( int i=0; i<8 ; i++ ) {
    threads[i] = std::thread( &printout_test ) ;
  }
  for( auto &t : threads ) {
    t.join() ;
  }
  threads.clear() ;
  
  
  return 0 ;
}