# search for VXL and include VXL configuration
find_package(VXL REQUIRED)
include(${VXL_CMAKE_DIR}/UseVXL.cmake)

# set compiler options; these have to come last to take precedence
set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g -ansi -pedantic -Wall -Wextra -Werror -Wno-long-long -DDEBUG")
set(CMAKE_CXX_FLAGS_RELEASE "-O2 -ansi -DNDEBUG -Wno-long-long")

include_directories(../include ${VXL_CORE_INCLUDE_DIR})

add_executable(phtrtest
  main.cpp
  )

target_link_libraries(phtrtest
  phtr
  vil
  vil_io
  vil_algo
  )
