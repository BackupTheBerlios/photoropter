project(phtrtest)

# search for VXL
find_package(VXL QUIET)

if(VXL_FOUND)
  include_directories(../include ${VXL_VCL_INCLUDE_DIR} ${VXL_CORE_INCLUDE_DIR})
  link_directories(${VXL_LIBRARY_DIR})

  add_executable(phtrtest
    phtrtest.cpp
    )

  target_link_libraries(phtrtest
    Photoropter
    vil
    vil_io
    vil_algo
    )
else(VXL_FOUND)
  message("VXL not found, test application will not be built. Check the VXL_DIR variable if this is an error.")
endif(VXL_FOUND)