########################################
# project settings
########################################

# require CMake 2.6 or higher
cmake_minimum_required(VERSION 2.6)

# project name
project(Photoropter)

# set default build type
if(NOT CMAKE_BUILD_TYPE)
  message("No build type set, defaulting to 'Debug'.")
  set(CMAKE_BUILD_TYPE
    "Debug"
    CACHE STRING "Build type (Debug|Release)" FORCE)
endif(NOT CMAKE_BUILD_TYPE)

# set usage of boost::scoped_ptr over std::auto_ptr (nice for debugging,
# but unnecessary build dependency afterwards)
set(PHTR_USE_SCOPED_PTR false CACHE BOOL
  "Use boost::scoped_ptr instead of std::auto_ptr where applicable")

# build documentation?
set(PHTR_BUILD_DOCUMENTATION true CACHE BOOL "Build Doxygen documentation")
set(PHTR_DOCUMENT_PRIVATE false CACHE BOOL "Include private members in documentation")

# build shared?
set(PHTR_SHARED false CACHE BOOL "Additionally build as a shared library")

########################################
# configure libraries
########################################

# search for Boost
find_package(Boost 1.38.0 REQUIRED)

# check for GCC 4.4 and older Boost versions to avoid ADL problems in GIL
if(CMAKE_COMPILER_IS_GNUCXX)
  execute_process(COMMAND
    "${CMAKE_CXX_COMPILER}" "-dumpversion"
    OUTPUT_VARIABLE GNU_CPP_VERSION
    OUTPUT_STRIP_TRAILING_WHITESPACE)
  if(NOT ${GNU_CPP_VERSION} VERSION_LESS 4.4
      AND ${Boost_MAJOR_VERSION}.${Boost_MINOR_VERSION} VERSION_LESS 1.41)
    message(FATAL_ERROR
      "Detected GCC ${GNU_CPP_VERSION} together with Boost "
      "${Boost_MAJOR_VERSION}.${Boost_MINOR_VERSION}.\n"
      "For GCC 4.4 support, at least Boost 1.41 is needed.")
  endif(NOT ${GNU_CPP_VERSION} VERSION_LESS 4.4
    AND ${Boost_MAJOR_VERSION}.${Boost_MINOR_VERSION} VERSION_LESS 1.41)
endif(CMAKE_COMPILER_IS_GNUCXX)

# set compiler options; these have to come last to take precedence
set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g -ansi -pedantic -Wall -Wextra -Werror -Wno-long-long -DDEBUG")
set(CMAKE_CXX_FLAGS_RELEASE "-O2 -ansi -DNDEBUG -Wno-long-long")

if(PHTR_USE_SCOPED_PTR)
  set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DUSE_BOOST_SCOPED_PTR")
  set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -DUSE_BOOST_SCOPED_PTR")
endif(PHTR_USE_SCOPED_PTR)

########################################
# doxygen documentation
########################################

if(PHTR_BUILD_DOCUMENTATION)
  find_package(Doxygen)

  if(DOXYGEN_FOUND)
    message(STATUS "HTML documentation will be generated.")

    set(DOXYGEN_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR})
    set(DOXYGEN_DOCSRC_DIR ${DOXYGEN_SRC_DIR}/doc-src)
    set(DOXYGEN_DOC_DIR ${CMAKE_CURRENT_BINARY_DIR}/doc)

    set(DOXYGEN_CONF_IN ${DOXYGEN_DOCSRC_DIR}/doxygen.conf.in)
    set(DOXYGEN_CONF ${DOXYGEN_DOC_DIR}/doxygen.conf)
    if(PHTR_DOCUMENT_PRIVATE)
      set(DOXYGEN_EXTRACT_PRIVATE "YES")
      set(DOXYGEN_EXTRACT_STATIC "YES")
    else(PHTR_DOCUMENT_PRIVATE)
      set(DOXYGEN_EXTRACT_PRIVATE "NO")
      set(DOXYGEN_EXTRACT_STATIC "NO")
    endif(PHTR_DOCUMENT_PRIVATE)

    configure_file(${DOXYGEN_CONF_IN} ${DOXYGEN_CONF})

    add_custom_target(doc ALL ${DOXYGEN_EXECUTABLE} ${DOXYGEN_CONF})

  else(DOXYGEN_FOUND)
    message("Doxygen not found, documentation will not be generated!")

  endif(DOXYGEN_FOUND)
endif(PHTR_BUILD_DOCUMENTATION)

########################################
# configure library components
########################################

set(PHTR_SOURCES
  include/types.h
  include/storagetypes.h
  include/image_view.h
  channel_storage.h
  exception.h
  exception.cpp
  image_view.cpp
  mem_image_view_r.h
  mem_image_view_r.tpl.h
  mem_image_r.h
  mem_image_r.cpp
  mem_layout.h
  mem_storage_info.h
  )

include_directories(include ${Boost_INCLUDE_DIR})

add_library(phtr STATIC ${PHTR_SOURCES})

if(PHTR_SHARED)
  add_library(phtr-shared SHARED ${PHTR_SOURCES})
  set_target_properties(phtr-shared PROPERTIES OUTPUT_NAME "pthr")
endif(PHTR_SHARED)

# test application is in a subdirectory
add_subdirectory(testapp)
