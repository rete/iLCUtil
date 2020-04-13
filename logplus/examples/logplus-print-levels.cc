
#include <logplus/logplus.h>

using namespace logplus::levels ;

#define PRINT_LEVEL( MLEVEL ) std::cout << "==> " << MLEVEL::name << ", level: " << MLEVEL::level << ", active? " << MLEVEL::active << std::endl ;

int main() {
  
  std::cout << "========= logplus config =========" << std::endl ;
  std::cout << "- min_level:          " << logplus::config::min_level << std::endl ;
  std::cout << "- max_level:          " << logplus::config::max_level << std::endl ;
  std::cout << "- debug_active:       " << logplus::config::debug_active << std::endl ;
  std::cout << "- message_active:     " << logplus::config::message_active << std::endl ;
  std::cout << "- warning_active:     " << logplus::config::warning_active << std::endl ;
  std::cout << "- error_active:       " << logplus::config::error_active << std::endl ;
  std::cout << "- verbosity levels:" << std::endl ;
  PRINT_LEVEL( DEBUG )
  PRINT_LEVEL( DEBUG0 )
  PRINT_LEVEL( DEBUG1 )
  PRINT_LEVEL( DEBUG2 )
  PRINT_LEVEL( DEBUG3 )
  PRINT_LEVEL( DEBUG4 )
  PRINT_LEVEL( DEBUG5 )
  PRINT_LEVEL( DEBUG6 )
  PRINT_LEVEL( DEBUG7 )
  PRINT_LEVEL( DEBUG8 )
  PRINT_LEVEL( DEBUG9 )
  PRINT_LEVEL( MESSAGE )
  PRINT_LEVEL( MESSAGE0 )
  PRINT_LEVEL( MESSAGE1 )
  PRINT_LEVEL( MESSAGE2 )
  PRINT_LEVEL( MESSAGE3 )
  PRINT_LEVEL( MESSAGE4 )
  PRINT_LEVEL( MESSAGE5 )
  PRINT_LEVEL( MESSAGE6 )
  PRINT_LEVEL( MESSAGE7 )
  PRINT_LEVEL( MESSAGE8 )
  PRINT_LEVEL( MESSAGE9 )
  PRINT_LEVEL( WARNING )
  PRINT_LEVEL( WARNING0 )
  PRINT_LEVEL( WARNING1 )
  PRINT_LEVEL( WARNING2 )
  PRINT_LEVEL( WARNING3 )
  PRINT_LEVEL( WARNING4 )
  PRINT_LEVEL( WARNING5 )
  PRINT_LEVEL( WARNING6 )
  PRINT_LEVEL( WARNING7 )
  PRINT_LEVEL( WARNING8 )
  PRINT_LEVEL( WARNING9 )
  PRINT_LEVEL( ERROR )
  PRINT_LEVEL( ERROR0 )
  PRINT_LEVEL( ERROR1 )
  PRINT_LEVEL( ERROR2 )
  PRINT_LEVEL( ERROR3 )
  PRINT_LEVEL( ERROR4 )
  PRINT_LEVEL( ERROR5 )
  PRINT_LEVEL( ERROR6 )
  PRINT_LEVEL( ERROR7 )
  PRINT_LEVEL( ERROR8 )
  PRINT_LEVEL( ERROR9 )
  std::cout << "========================================" << std::endl ;
  
  return 0 ;
}