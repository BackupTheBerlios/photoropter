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

########################################
# configure libraries
########################################

# search for VXL and include VXL configuration
find_package(VXL REQUIRED)
include(${VXL_CMAKE_DIR}/UseVXL.cmake)

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

set(PHTR_BUILD_DOCUMENTATION true CACHE BOOL "Build Doxygen documentation")

if(PHTR_BUILD_DOCUMENTATION)
  find_package(Doxygen)

  if(DOXYGEN_FOUND)
    message(STATUS "HTML documentation will be generated.")

    set(DOXYGEN_CONF_IN ${CMAKE_CURRENT_SOURCE_DIR}/doxygen.conf.in)
    set(DOXYGEN_CONF ${CMAKE_CURRENT_BINARY_DIR}/doxygen.conf)
    set(DOXYGEN_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR})
    set(DOXYGEN_DOC_DIR ${CMAKE_CURRENT_BINARY_DIR}/doc)

    configure_file(${DOXYGEN_CONF_IN} ${DOXYGEN_CONF})

    add_custom_target(doc ALL ${DOXYGEN_EXECUTABLE} ${DOXYGEN_CONF})

  else(DOXYGEN_FOUND)
    message("Doxygen not found, documentation will not be generated!")

  endif(DOXYGEN_FOUND)
endif(PHTR_BUILD_DOCUMENTATION)

########################################
# configure program components
########################################

include_directories(${VXL_CORE_INCLUDE_DIR} ${Boost_INCLUDE_DIR})

add_executable(phtr_test
  main.cpp
  types.h
  storagetypes.h
  exception.h
  exception.cpp
  image_view.h
  image_view.cpp
  mem_image_view_r.h
  mem_image_view_r.cpp
  mem_image_r.h
  mem_image_r.cpp
  mem_storage_info.h
  )

target_link_libraries(phtr_test
  vil
  vil_io
  vil_algo
  )
