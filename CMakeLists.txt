########################################
# project settings
########################################

# require CMake 2.6 or higher
cmake_minimum_required(VERSION 2.6)

# project name
project(photoropter)

# set default build type
if(NOT CMAKE_BUILD_TYPE)
  message("No build type set, defaulting to 'Debug'.")
  set(CMAKE_BUILD_TYPE
    "Debug"
    CACHE STRING "Build type (Debug|Release)" FORCE)

  # set default compiler options
  if(CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g -ansi -pedantic -Wall -Wextra -Werror -Wno-long-long -DDEBUG")
    set(CMAKE_CXX_FLAGS_RELEASE "-O3 -ffast-math -fomit-frame-pointer -ansi -Wno-long-long -DNDEBUG")
  endif(CMAKE_COMPILER_IS_GNUCXX)

  # override default cache values set by CMake
  set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG}"
    CACHE STRING "Compiler options for debug builds" FORCE)
  set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE}"
    CACHE STRING "Compiler options for release builds" FORCE)
endif(NOT CMAKE_BUILD_TYPE)

# build documentation?
set(PHTR_BUILD_DOCUMENTATION false CACHE BOOL "Build Doxygen documentation")
set(PHTR_DOCUMENT_ALL false CACHE BOOL "Build documentation for all library files")
set(PHTR_DOCUMENT_PRIVATE false CACHE BOOL "Include private members in documentation")

# build shared?
set(PHTR_SHARED true CACHE BOOL "Additionally build as a shared library")

set(PHTR_PARALLELISE true CACHE BOOL "Use parallelised code if possible (OpenMP)")

########################################
# configure libraries
########################################

# OpenMP
find_package(OpenMP)

if(OPENMP_FOUND AND PHTR_PARALLELISE)
  message(STATUS "OpenMP found: parallel code will be used for release build.")
  set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} ${OpenMP_CXX_FLAGS} -DHAVE_OPENMP")
endif()

########################################
# doxygen documentation
########################################

find_package(Doxygen)

if(DOXYGEN_FOUND)
  message(STATUS "Doxygen found: HTML documentation can be generated.")

  # set directories
  set(DOXYGEN_SRC_DIR1 ${CMAKE_CURRENT_SOURCE_DIR}/include/${CMAKE_PROJECT_NAME})
  set(DOXYGEN_SRC_DIR2 ${CMAKE_CURRENT_SOURCE_DIR}/src)
  set(DOXYGEN_DOCSRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/doc-src)
  set(DOXYGEN_DOC_DIR ${CMAKE_CURRENT_BINARY_DIR}/doc)

  set(DOXYGEN_CONF_IN ${DOXYGEN_DOCSRC_DIR}/doxygen.conf.in)
  set(DOXYGEN_CONF ${CMAKE_CURRENT_BINARY_DIR}/doxygen.conf)

  # now set variables that will be used by doxygen itself
  set(DOXY_DOCSRC_DIR "\"${DOXYGEN_DOCSRC_DIR}\"")
  set(DOXY_DOC_DIR "\"${DOXYGEN_DOC_DIR}\"")

  set(DOXY_CSS "\"${DOXYGEN_DOCSRC_DIR}/customdoxy.css\"")
  set(DOXY_PROJECT "\"${CMAKE_PROJECT_NAME}\"")

  set(DOXY_INPUT "\"${DOXYGEN_SRC_DIR1}\"")
  set(DOXY_INPUT "${DOXY_INPUT} \"${DOXYGEN_SRC_DIR2}\"")
  set(DOXY_INPUT "${DOXY_INPUT} \"${DOXYGEN_DOCSRC_DIR}\"")
  set(DOXY_INPUT "${DOXY_INPUT} \"${DOXYGEN_DOCSRC_DIR}/main.txt\"")
  set(DOXY_INPUT "${DOXY_INPUT} \"${DOXYGEN_DOCSRC_DIR}/overview.txt\"")
  set(DOXY_INPUT "${DOXY_INPUT} \"${DOXYGEN_DOCSRC_DIR}/license.txt\"")
  set(DOXY_INPUT "${DOXY_INPUT} \"${DOXYGEN_DOCSRC_DIR}/codingstyle.txt\"")
  set(DOXY_INPUT "${DOXY_INPUT} \"${DOXYGEN_DOCSRC_DIR}/techback.txt\"")

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

set(PHTR_INCLUDE_DIR "include/${CMAKE_PROJECT_NAME}")
set(PHTR_SRC_DIR "src")

set(PHTR_SOURCES
  ${PHTR_INCLUDE_DIR}/types.h
  ${PHTR_INCLUDE_DIR}/storage_type.h
  ${PHTR_INCLUDE_DIR}/channel_type.h
  ${PHTR_INCLUDE_DIR}/interpolation_type.h
  ${PHTR_INCLUDE_DIR}/image_buffer.h
  ${PHTR_INCLUDE_DIR}/image_buffer.tpl.h
  ${PHTR_INCLUDE_DIR}/image_interpolator.h
  ${PHTR_INCLUDE_DIR}/channel_storage.h
  ${PHTR_INCLUDE_DIR}/exception.h
  ${PHTR_INCLUDE_DIR}/channel_range.h
  ${PHTR_INCLUDE_DIR}/mem_image_view_base.h
  ${PHTR_INCLUDE_DIR}/mem_image_view_base.tpl.h
  ${PHTR_INCLUDE_DIR}/mem_image_view_r.h
  ${PHTR_INCLUDE_DIR}/mem_image_view_r.tpl.h
  ${PHTR_INCLUDE_DIR}/mem_image_view_w.h
  ${PHTR_INCLUDE_DIR}/mem_image_view_w.tpl.h
  ${PHTR_INCLUDE_DIR}/mem_image_iter_base.h
  ${PHTR_INCLUDE_DIR}/mem_image_iter_base.tpl.h
  ${PHTR_INCLUDE_DIR}/mem_image_iter_r.h
  ${PHTR_INCLUDE_DIR}/mem_image_iter_r.tpl.h
  ${PHTR_INCLUDE_DIR}/mem_image_iter_w.h
  ${PHTR_INCLUDE_DIR}/mem_image_iter_w.tpl.h
  ${PHTR_INCLUDE_DIR}/image_interpolator.tpl.h
  ${PHTR_INCLUDE_DIR}/mem_layout.h
  ${PHTR_INCLUDE_DIR}/mem_storage_info.h
  ${PHTR_INCLUDE_DIR}/image_transform.h
  ${PHTR_INCLUDE_DIR}/image_transform.tpl.h
  ${PHTR_INCLUDE_DIR}/correction_model_base.h
  ${PHTR_INCLUDE_DIR}/geom_correction_model.h
  ${PHTR_INCLUDE_DIR}/geom_correction_queue.h
  ${PHTR_INCLUDE_DIR}/geom_correction_queue.inl.h
  ${PHTR_INCLUDE_DIR}/colour_correction_model.h
  ${PHTR_INCLUDE_DIR}/colour_correction_queue.h
  ${PHTR_INCLUDE_DIR}/colour_correction_queue.inl.h
  ${PHTR_SRC_DIR}/correction_model_base.cpp
  ${PHTR_SRC_DIR}/geom_correction_model.cpp
  ${PHTR_SRC_DIR}/geom_correction_queue.cpp
  ${PHTR_SRC_DIR}/colour_correction_model.cpp
  ${PHTR_SRC_DIR}/colour_correction_queue.cpp
  ${PHTR_SRC_DIR}/exception.cpp
  )

include_directories(include)

add_library(${CMAKE_PROJECT_NAME} STATIC ${PHTR_SOURCES})

if(PHTR_SHARED)
  add_library(phtr-shared SHARED ${PHTR_SOURCES})
  set_target_properties(phtr-shared PROPERTIES OUTPUT_NAME "${CMAKE_PROJECT_NAME}")
endif(PHTR_SHARED)

# test application is in a subdirectory
add_subdirectory(testapp)
