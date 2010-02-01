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
set(PHTR_DOCUMENT_ALL false CACHE BOOL "Build documentation for all library files")
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
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -ffast-math -march=k8 -ansi -DNDEBUG -Wno-long-long")

if(PHTR_USE_SCOPED_PTR)
  set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DUSE_BOOST_SCOPED_PTR")
  set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -DUSE_BOOST_SCOPED_PTR")
endif(PHTR_USE_SCOPED_PTR)

########################################
# doxygen documentation
########################################

find_package(Doxygen)

if(DOXYGEN_FOUND)
  message(STATUS "Doxygen found: HTML documentation can be generated.")

  set(DOXYGEN_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
  set(DOXYGEN_DOCSRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/doc-src)
  set(DOXYGEN_DOC_DIR ${CMAKE_CURRENT_BINARY_DIR}/doc)

  set(DOXYGEN_CONF_IN ${DOXYGEN_DOCSRC_DIR}/doxygen.conf.in)
  set(DOXYGEN_CONF ${CMAKE_CURRENT_BINARY_DIR}/doxygen.conf)

  # now set variables that will be used by doxygen itself
  set(DOXY_DOCSRC_DIR "\"${DOXYGEN_DOCSRC_DIR}\"")
  set(DOXY_DOC_DIR "\"${DOXYGEN_DOC_DIR}\"")

  set(DOXY_CSS "\"${DOXYGEN_DOCSRC_DIR}/customdoxy.css\"")
  set(DOXY_PROJECT "\"${CMAKE_PROJECT_NAME}\"")

  set(DOXY_INPUT "\"${DOXYGEN_SRC_DIR}\"")
  set(DOXY_INPUT "${DOXY_INPUT} \"${DOXYGEN_DOCSRC_DIR}\"")
  set(DOXY_INPUT "${DOXY_INPUT} \"${DOXYGEN_DOCSRC_DIR}/main.txt\"")
  set(DOXY_INPUT "${DOXY_INPUT} \"${DOXYGEN_DOCSRC_DIR}/overview.txt\"")
  set(DOXY_INPUT "${DOXY_INPUT} \"${DOXYGEN_DOCSRC_DIR}/license.txt\"")
  set(DOXY_INPUT "${DOXY_INPUT} \"${DOXYGEN_DOCSRC_DIR}/codingstyle.txt\"")

  if(PHTR_DOCUMENT_ALL)
    set(DOXY_INPUT "${DOXY_INPUT} \"${CMAKE_CURRENT_SOURCE_DIR}\"")

    if(PHTR_DOCUMENT_PRIVATE)
      set(DOXY_EXTRACT_PRIVATE "YES")
      set(DOXY_EXTRACT_STATIC "YES")
    else(PHTR_DOCUMENT_PRIVATE)
      set(DOXY_EXTRACT_PRIVATE "NO")
      set(DOXY_EXTRACT_STATIC "NO")
    endif(PHTR_DOCUMENT_PRIVATE)

  else(PHTR_DOCUMENT_ALL)
    set(DOXY_EXTRACT_PRIVATE "NO")
    set(DOXY_EXTRACT_STATIC "NO")
  endif(PHTR_DOCUMENT_ALL)

  configure_file(${DOXYGEN_CONF_IN} ${DOXYGEN_CONF})

  # if documentation is not requested, add target, but not as default
  if(PHTR_BUILD_DOCUMENTATION)
    message(STATUS "Documentation will be generated in default build.")
    add_custom_target(doc ALL ${DOXYGEN_EXECUTABLE} ${DOXYGEN_CONF})
  else(PHTR_BUILD_DOCUMENTATION)
    message(STATUS "Documentation will not be generated in default build.")
    add_custom_target(doc ${DOXYGEN_EXECUTABLE} ${DOXYGEN_CONF})
  endif(PHTR_BUILD_DOCUMENTATION)

else(DOXYGEN_FOUND)
  message("Doxygen not found: documentation cannnot be generated.")

endif(DOXYGEN_FOUND)

########################################
# configure library components
########################################

set(PHTR_SOURCES
  include/types.h
  include/storage_type.h
  include/channel_type.h
  include/image_buffer.h
  include/image_buffer.tpl.h
  include/image_interpolator.h
  include/channel_storage.h
  include/exception.h
  include/channel_range.h
  include/mem_image_view_base.h
  include/mem_image_view_base.tpl.h
  include/mem_image_view_r.h
  include/mem_image_view_r.tpl.h
  include/mem_image_view_w.h
  include/mem_image_view_w.tpl.h
  include/mem_image_view_iter_w.h
  include/mem_image_view_iter_w.tpl.h
  include/image_interpolator.tpl.h
  include/mem_layout.h
  include/mem_storage_info.h
  include/image_transform.h
  include/image_transform.tpl.h
  exception.cpp
  )

include_directories(include ${Boost_INCLUDE_DIR})

add_library(phtr STATIC ${PHTR_SOURCES})

if(PHTR_SHARED)
  add_library(phtr-shared SHARED ${PHTR_SOURCES})
  set_target_properties(phtr-shared PROPERTIES OUTPUT_NAME "pthr")
endif(PHTR_SHARED)

# test application is in a subdirectory
add_subdirectory(testapp)
