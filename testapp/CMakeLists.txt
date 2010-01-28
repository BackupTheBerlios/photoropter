# search for VXL
find_package(VXL REQUIRED)

include_directories(../include ${VXL_VCL_INCLUDE_DIR} ${VXL_CORE_INCLUDE_DIR})
link_directories(${VXL_LIBRARY_DIR})

add_executable(phtrtest
  main.cpp
  )

target_link_libraries(phtrtest
  phtr
  vil
  vil_io
  vil_algo
  )
