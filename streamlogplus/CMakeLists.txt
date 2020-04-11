########################################################
# cmake file for building streamlogplus 
# @author Remi Ete, DESY
cmake_minimum_required( VERSION 3.14 FATAL_ERROR )
########################################################

# project settings
project( streamlogplus 
  DESCRIPTION "Logging library based on streamlog, for multi-threading usage"
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

aux_source_directory( source/src streamlogplus_sources )
add_library( streamlogplus SHARED ${streamlogplus_sources} )
add_library( streamlogplus::streamlogplus ALIAS streamlogplus )
install( TARGETS streamlogplus EXPORT streamlogplus LIBRARY )
target_link_libraries( streamlogplus PUBLIC fmt::fmt std::filesystem Threads::Threads )
target_include_directories( 
  streamlogplus BEFORE PUBLIC 
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/source/include>
  $<INSTALL_INTERFACE:include> # source/include here ???
)
set_target_properties( 
  streamlogplus
  PROPERTIES 
    VERSION ${${PROJECT_NAME}_VERSION}
    CXX_STANDARD ${CMAKE_CXX_STANDARD}
)
install( DIRECTORY source/include/streamlogplus TYPE INCLUDE )

set( streamlogplus_examples streamlog-print-levels streamlog-simple )
foreach( binary ${streamlogplus_examples} )
  add_executable( example_${binary} examples/${binary}.cc )
  target_link_libraries( example_${binary} streamlogplus::streamlogplus )
  set_target_properties( example_${binary} PROPERTIES OUTPUT_NAME ${binary} )
  install( TARGETS example_${binary} RUNTIME )
endforeach()
 
# display some variables and write them to cache
display_std_variables()


# TODO: missing exports
