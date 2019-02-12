## Set the default compiler flags for all projects picking up default ilcutil settings
## This runs checks if compilers support the flag and sets them, if they do
## this will create a humongous amount of warnings when compiling :)

INCLUDE(CheckCXXCompilerFlag)

SET(COMPILER_FLAGS -Wall -Wextra -Wshadow -Weffc++ -pedantic -Wno-long-long -Wuninitialized )

IF( "${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU" )
 LIST( APPEND COMPILER_FLAGS -Wl,-no-undefined )
ENDIF()


MESSAGE( STATUS "FLAGS ${COMPILER_FLAGS}" )
FOREACH( FLAG ${COMPILER_FLAGS} )

  ## meed to replace the minus or plus signs from the variables, because it is passed
  ## as a macro to g++ which causes a warning about no whitespace after macro
  ## definition
  STRING(REPLACE "-" "_" FLAG_WORD ${FLAG} )
  STRING(REPLACE "+" "P" FLAG_WORD ${FLAG_WORD} )

  CHECK_CXX_COMPILER_FLAG( "${FLAG}" CXX_FLAG_WORKS_${FLAG_WORD} )
  IF( ${CXX_FLAG_WORKS_${FLAG_WORD}} )
    MESSAGE ( STATUS "Adding ${FLAG} to CXX_FLAGS" )
    ### We prepend the flag, so they are overwritten by whatever the user sets in his own configuration
    SET ( CMAKE_CXX_FLAGS "${FLAG} ${CMAKE_CXX_FLAGS}")
  ELSE()
    MESSAGE ( STATUS "NOT Adding ${FLAG} to CXX_FLAGS" )
  ENDIF()
ENDFOREACH()

OPTION( USE_CXX11 "Use CXX Standard 2011" True )
OPTION( USE_CXX14 "Use CXX Standard 2014" False )
OPTION( USE_CXX17 "Use CXX Standard 2017" False )
OPTION( USE_CXX20 "Use CXX Standard 2020" False )

FUNCTION( SET_CPP_STANDARD _std _flag )
  SET( FLAG "-std=${_std}" )
  SET( FLAG_WORD "std${_flag}" )
  CHECK_CXX_COMPILER_FLAG( ${FLAG} CXX_FLAG_WORKS_${FLAG_WORD} )
  IF( ${CXX_FLAG_WORKS_${FLAG_WORD}} )
    SET( CMAKE_CXX_FLAGS "${FLAG} ${CMAKE_CXX_FLAGS}")
  ELSE()
    MESSAGE( FATAL_ERROR "Cannot add ${FLAG} to CMAKE_CXX_FLAGS, but ${_std} standard was requested, check your compiler" )
  ENDIF()
ENDFUNCTION( SET_CPP_STANDARD )

IF( USE_CXX20 )
  SET_CPP_STANDARD( "c++20" "CXX20" )
ELSEIF( USE_CXX17 )
  SET_CPP_STANDARD( "c++17" "CXX17" )
ELSEIF( USE_CXX14 )
  SET_CPP_STANDARD( "c++14" "CXX14" )
ELSEIF( USE_CXX11 )
  SET_CPP_STANDARD( "c++11" "CXX11" )
ELSE()
  MESSAGE( STATUS "C++ standard not specified. Using default one from compiler !" )
ENDIF()

IF( "${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU" AND CMAKE_CXX_COMPILER_VERSION VERSION_GREATER 4.9 )
  SET( CMAKE_CXX_FLAGS "-fdiagnostics-color=auto ${CMAKE_CXX_FLAGS}" )
ENDIF()
