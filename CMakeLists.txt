########################################
# project settings
########################################

# require CMake 2.6 or higher
cmake_minimum_required(VERSION 2.6)

# project name
project(photoropter)

# version
set(photoropter_VERSION_MAJOR "0")
set(photoropter_VERSION_MINOR "0")
set(photoropter_VERSION_PATCH "7b")
set(photoropter_VERSION 
  "${photoropter_VERSION_MAJOR}.${photoropter_VERSION_MINOR}.${photoropter_VERSION_PATCH}")

# package maintainer
set(photoropter_MAINTAINER "Robert Fendt <robertfendt@users.berlios.de")

# the library basename
set(PHTR_LIB_NAME ${CMAKE_PROJECT_NAME})

# set default build type
if(NOT CMAKE_BUILD_TYPE)
  message("No build type set, defaulting to 'Debug'.")
  set(CMAKE_BUILD_TYPE
    "Debug"
    CACHE STRING "Build type (Debug|Release)" FORCE)

  # set default compiler options
  if(CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0 -g -Wall -Wextra -Werror -pedantic -ansi -Wno-long-long")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -ffast-math -fomit-frame-pointer -ansi -Wno-long-long")
  endif(CMAKE_COMPILER_IS_GNUCXX)
  
  if(MSVC)
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /Ox /Ot /Oy /GT /Ob2")
  endif(MSVC)

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
# configure external libraries
########################################

# OpenMP
find_package(OpenMP)

if(OPENMP_FOUND AND PHTR_PARALLELISE)
  message(STATUS "OpenMP found: parallel code will be used for release build.")
  set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} ${OpenMP_CXX_FLAGS} -DHAVE_OPENMP")

  # check compilers with known support for OpenMP3
  if(CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -DOPENMP3")
  endif(CMAKE_COMPILER_IS_GNUCXX)
endif()

########################################
# configure, build doxygen documentation
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
  set(DOXY_INPUT "${DOXY_INPUT} \"${DOXYGEN_DOCSRC_DIR}/tutorial.txt\"")

  if(PHTR_DOCUMENT_ALL)
    set(DOXY_ENABLED_SECTIONS "PROTECTED")

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
# configure, build library components
########################################

set(PHTR_INCLUDE_DIR "include/${CMAKE_PROJECT_NAME}")
set(PHTR_SRC_DIR "src")

# set the Photoropter sources
set(PHTR_INCLUDES
  ${PHTR_INCLUDE_DIR}/geom/fisheye_equidist.h
  ${PHTR_INCLUDE_DIR}/geom/fisheye_equidist.inl.h
  ${PHTR_INCLUDE_DIR}/geom/fisheye_equisolid.h
  ${PHTR_INCLUDE_DIR}/geom/fisheye_equisolid.inl.h
  ${PHTR_INCLUDE_DIR}/geom/fisheye_ortho.h
  ${PHTR_INCLUDE_DIR}/geom/fisheye_ortho.inl.h
  ${PHTR_INCLUDE_DIR}/geom/fisheye_stereo.h
  ${PHTR_INCLUDE_DIR}/geom/fisheye_stereo.inl.h
  ${PHTR_INCLUDE_DIR}/geom/rectilinear.h
  ${PHTR_INCLUDE_DIR}/geom/rectilinear.inl.h
  ${PHTR_INCLUDE_DIR}/interpolator/interpolator_base.h
  ${PHTR_INCLUDE_DIR}/interpolator/interpolator_base.tpl.h
  ${PHTR_INCLUDE_DIR}/interpolator/interpolator_bilinear.h
  ${PHTR_INCLUDE_DIR}/interpolator/interpolator_bilinear.tpl.h
  ${PHTR_INCLUDE_DIR}/interpolator/interpolator_lanczos.h
  ${PHTR_INCLUDE_DIR}/interpolator/interpolator_lanczos.tpl.h
  ${PHTR_INCLUDE_DIR}/interpolator/interpolator_nn.h
  ${PHTR_INCLUDE_DIR}/interpolator/interpolator_nn.tpl.h
  ${PHTR_INCLUDE_DIR}/mem/channel_range.h
  ${PHTR_INCLUDE_DIR}/mem/channel_storage.h
  ${PHTR_INCLUDE_DIR}/mem/channel_type.h
  ${PHTR_INCLUDE_DIR}/mem/colour_tuple.h
  ${PHTR_INCLUDE_DIR}/mem/colour_tuple.tpl.h
  ${PHTR_INCLUDE_DIR}/mem/coord_tuple.h
  ${PHTR_INCLUDE_DIR}/mem/coord_tuple.tpl.h
  ${PHTR_INCLUDE_DIR}/mem/mem_layout.h
  ${PHTR_INCLUDE_DIR}/mem/mem_storage_info.h
  ${PHTR_INCLUDE_DIR}/mem/storage_type.h
  ${PHTR_INCLUDE_DIR}/model/colour_correction_model.h
  ${PHTR_INCLUDE_DIR}/model/correction_model_base.h
  ${PHTR_INCLUDE_DIR}/model/geometry_convert_pixel_model.h
  ${PHTR_INCLUDE_DIR}/model/geometry_convert_pixel_model.tpl.h
  ${PHTR_INCLUDE_DIR}/model/pixel_correction_model.h
  ${PHTR_INCLUDE_DIR}/model/ptlens_pixel_model.h
  ${PHTR_INCLUDE_DIR}/model/scaler_pixel_model.h
  ${PHTR_INCLUDE_DIR}/model/subpixel_correction_model.h
  ${PHTR_INCLUDE_DIR}/model/vignetting_colour_model.h
  ${PHTR_INCLUDE_DIR}/colour_correction_queue.h
  ${PHTR_INCLUDE_DIR}/colour_correction_queue.tpl.h
  ${PHTR_INCLUDE_DIR}/exception.h
  ${PHTR_INCLUDE_DIR}/gamma_func.h
  ${PHTR_INCLUDE_DIR}/geometry_type.h
  ${PHTR_INCLUDE_DIR}/image_buffer.h
  ${PHTR_INCLUDE_DIR}/image_buffer.tpl.h
  ${PHTR_INCLUDE_DIR}/image_transform.h
  ${PHTR_INCLUDE_DIR}/image_transform.tpl.h
  ${PHTR_INCLUDE_DIR}/interpolation_type.h
  ${PHTR_INCLUDE_DIR}/mem_image_iter_base.h
  ${PHTR_INCLUDE_DIR}/mem_image_iter_base.tpl.h
  ${PHTR_INCLUDE_DIR}/mem_image_iter_r.h
  ${PHTR_INCLUDE_DIR}/mem_image_iter_r.tpl.h
  ${PHTR_INCLUDE_DIR}/mem_image_iter_w.h
  ${PHTR_INCLUDE_DIR}/mem_image_iter_w.tpl.h
  ${PHTR_INCLUDE_DIR}/mem_image_view_base.h
  ${PHTR_INCLUDE_DIR}/mem_image_view_base.tpl.h
  ${PHTR_INCLUDE_DIR}/mem_image_view_r.h
  ${PHTR_INCLUDE_DIR}/mem_image_view_r.tpl.h
  ${PHTR_INCLUDE_DIR}/mem_image_view_w.h
  ${PHTR_INCLUDE_DIR}/mem_image_view_w.tpl.h
  ${PHTR_INCLUDE_DIR}/pixel_correction_queue.h
  ${PHTR_INCLUDE_DIR}/pixel_correction_queue.inl.h
  ${PHTR_INCLUDE_DIR}/subpixel_correction_queue.h
  ${PHTR_INCLUDE_DIR}/subpixel_correction_queue.tpl.h
  ${PHTR_INCLUDE_DIR}/types.h
  ${PHTR_INCLUDE_DIR}/util.h
  )

set(PHTR_SOURCES
  ${PHTR_SRC_DIR}/mem/mem_layout.cpp
  ${PHTR_SRC_DIR}/model/correction_model_base.cpp
  ${PHTR_SRC_DIR}/model/geometry_convert_pixel_model.cpp
  ${PHTR_SRC_DIR}/model/ptlens_pixel_model.cpp
  ${PHTR_SRC_DIR}/model/scaler_pixel_model.cpp
  ${PHTR_SRC_DIR}/model/vignetting_colour_model.cpp
  ${PHTR_SRC_DIR}/colour_correction_queue.cpp
  ${PHTR_SRC_DIR}/exception.cpp
  ${PHTR_SRC_DIR}/gamma_func.cpp
  ${PHTR_SRC_DIR}/modpar_emor.h
  ${PHTR_SRC_DIR}/modpar_invemor.h
  ${PHTR_SRC_DIR}/pixel_correction_queue.cpp
  ${PHTR_SRC_DIR}/subpixel_correction_queue.cpp
  )

configure_file(${PHTR_INCLUDE_DIR}/version.h.in
  ${CMAKE_CURRENT_BINARY_DIR}/${PHTR_INCLUDE_DIR}/version.h)

# the include directory to use: just 'include', since the
# photoropter subdirectory is already referenced in the headers
include_directories(include ${CMAKE_CURRENT_BINARY_DIR}/include)

# create static library
add_library(phtr-static STATIC ${PHTR_INCLUDES} ${PHTR_SOURCES})
set_target_properties(phtr-static
  PROPERTIES
  OUTPUT_NAME "${PHTR_LIB_NAME}"
  VERSION ${photoropter_VERSION_MAJOR}.${photoropter_VERSION_MINOR}.${photoropter_VERSION_PATCH}
  SOVERSION ${photoropter_VERSION_MAJOR}.${photoropter_VERSION_MINOR}
  )

# create shared library if needed
if(PHTR_SHARED)
  add_library(phtr-shared SHARED ${PHTR_INCLUDES} ${PHTR_SOURCES})
  set_target_properties(phtr-shared
    PROPERTIES
    OUTPUT_NAME "${PHTR_LIB_NAME}"
    VERSION ${photoropter_VERSION_MAJOR}.${photoropter_VERSION_MINOR}.${photoropter_VERSION_PATCH}
    SOVERSION ${photoropter_VERSION_MAJOR}.${photoropter_VERSION_MINOR}
    )
endif(PHTR_SHARED)

# the test application is in a subdirectory
add_subdirectory(testapp)

########################################
# Installation
########################################

install(TARGETS
  phtr-static
  DESTINATION lib
  COMPONENT dev
  )

if(PHTR_SHARED)
  install(TARGETS
    phtr-shared
    DESTINATION lib
    COMPONENT bin
    )
endif(PHTR_SHARED)

install(FILES
  ${PHTR_INCLUDES}
  DESTINATION ${PHTR_INCLUDE_DIR}
  COMPONENT dev
  )

install(FILES
  ${CMAKE_CURRENT_BINARY_DIR}/${PHTR_INCLUDE_DIR}/version.h
  DESTINATION ${PHTR_INCLUDE_DIR}
  )

########################################
# CPack: package generation
########################################

# include needed runtime components
include(InstallRequiredSystemLibraries)

# license file to be displayed in binary installers
set(CPACK_RESOURCE_FILE_LICENSE
  "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE.txt"
  )

set(CPACK_PACKAGE_CONTACT ${photoropter_MAINTAINER})
set(CPACK_PACKAGE_VERSION_MAJOR ${photoropter_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${photoropter_VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH ${photoropter_VERSION_PATCH})

include(CPack)
