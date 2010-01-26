########################################
# project settings
########################################

# require CMake 2.6 or higher
cmake_minimum_required(VERSION 2.6)

# project name
project(vxltest)

# set default build type
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE
    "Debug"
    CACHE STRING "Build type (Debug|Release)" FORCE)
endif(NOT CMAKE_BUILD_TYPE)

# set usage of boost::scoped_ptr over std::auto_ptr (nice for debugging,
# but unnecessary build dependency afterwards)
if(NOT USE_BOOST_SCOPED_PTR)
  set(USE_BOOST_SCOPED_PTR
  false
  CACHE BOOL "Use boost::scoped_ptr instead of std::auto_ptr where applicable" FORCE)
endif(NOT USE_BOOST_SCOPED_PTR)

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
set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g -ansi -pedantic -Wall -Wextra -Werror -DDEBUG")
set(CMAKE_CXX_FLAGS_RELEASE "-O2 -ansi -DNDEBUG")

if(USE_BOOST_SCOPED_PTR)
  set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DUSE_BOOST_SCOPED_PTR")
  set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -DUSE_BOOST_SCOPED_PTR")
endif(USE_BOOST_SCOPED_PTR)

########################################
# doxygen
########################################

find_package(Doxygen)

if(DOXYGEN_FOUND)
  message("Generating HTML documentation.")

  set(DOXYGEN_CONF_IN ${CMAKE_CURRENT_SOURCE_DIR}/doxygen.conf.in)
  set(DOXYGEN_CONF ${CMAKE_CURRENT_BINARY_DIR}/doxygen.conf)
  set(DOXYGEN_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR})
  set(DOXYGEN_DOC_DIR ${CMAKE_CURRENT_BINARY_DIR}/doc-src)

  configure_file(${DOXYGEN_CONF_IN} ${DOXYGEN_CONF})

  add_custom_target(doc ALL ${DOXYGEN_EXECUTABLE} ${DOXYGEN_CONF})

else(DOXYGEN_FOUND)
  message("Doxygen not found, documentation will not be generated.")

endif(DOXYGEN_FOUND)

########################################
# configure program components
########################################

include_directories(${VXL_CORE_INCLUDE_DIR} ${Boost_INCLUDE_DIR})

add_executable(vxltest
  main.cpp
  types.h
  storagetypes.h
  storagetypes.cpp
  gil_storagetypes.h
  exception.h
  exception.cpp
  basic_image.h
  basic_image.cpp
  basic_image_impl.h
  basic_image_impl.cpp
  image_impl.h
  image_impl.hpp
  image_view.h
  )

target_link_libraries(vxltest
  vil
  vil_io
  vil_algo
  )
