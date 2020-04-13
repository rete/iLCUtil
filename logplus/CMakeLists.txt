########################################################
# cmake file for building logplus 
# @author Remi Ete, DESY
cmake_minimum_required( VERSION 3.14 FATAL_ERROR )
########################################################

# project settings
project( logplus 
  DESCRIPTION "Simple logging library designed for multi-threading usage"
  VERSION 0.1.0
  LANGUAGES CXX
)

include( ilcsoft_default_settings )

if( NOT CMAKE_CXX_STANDARD )
  set( CMAKE_CXX_STANDARD 17 )
endif()

find_package( fmt REQUIRED )
find_package( Filesystem REQUIRED )
find_package( Threads REQUIRED )

### LIBRARY #################################################################

aux_source_directory( source/src logplus_sources )
add_library( logplus SHARED ${logplus_sources} )
add_library( logplus::streamlogplus ALIAS logplus )
install( TARGETS logplus EXPORT logplus LIBRARY )
target_link_libraries( logplus PUBLIC fmt::fmt std::filesystem Threads::Threads )
target_include_directories( 
  logplus BEFORE PUBLIC 
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/source/include>
  $<INSTALL_INTERFACE:include> # source/include here ???
)
set_target_properties( 
  logplus
  PROPERTIES 
    VERSION ${${PROJECT_NAME}_VERSION}
    CXX_STANDARD ${CMAKE_CXX_STANDARD}
)
install( DIRECTORY source/include/logplus TYPE INCLUDE )

set( logplus_examples logplus-print-levels logplus-simple )
foreach( binary ${logplus_examples} )
  add_executable( example_${binary} examples/${binary}.cc )
  target_link_libraries( example_${binary} logplus::logplus )
  set_target_properties( example_${binary} PROPERTIES OUTPUT_NAME ${binary} )
  install( TARGETS example_${binary} RUNTIME )
endforeach()
 
# display some variables and write them to cache
display_std_variables()


# TODO: missing exports
