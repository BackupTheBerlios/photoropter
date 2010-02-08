project(phtrtest)

# search for VXL
find_package(VXL QUIET)

#search for Boost
find_package(Boost 1.38 QUIET COMPONENTS program_options)

set(PHTR_BUILD_TESTAPP true)

if(NOT VXL_FOUND)
  message("VXL not found, test application will not be built. Check the VXL_DIR variable if this is an error.")
  set(PHTR_BUILD_TESTAPP false)
endif(NOT VXL_FOUND)

if(NOT Boost_FOUND)
  message("Boost was not found, test application will not be built. Make sure that you have Boost 1.38.0 or higher installed.")
  set(PHTR_BUILD_TESTAPP false)
endif(NOT Boost_FOUND)

if(PHTR_BUILD_TESTAPP)

  include_directories(../include ${VXL_VCL_INCLUDE_DIR} ${VXL_CORE_INCLUDE_DIR} ${Boost_INCLUDE_DIRS})
  link_directories(${VXL_LIBRARY_DIR} ${Boost_LIBRARY_DIRS})

  add_executable(phtrtest
    phtrtest.cpp
    )
  add_executable(phtrtest2
    phtrtest2.cpp
    )

  target_link_libraries(phtrtest
    photoropter
    vil
    vil_io
    ${Boost_LIBRARIES}
    )

  target_link_libraries(phtrtest2
    photoropter
    vil
    vil_io
    ${Boost_LIBRARIES}
    )

endif(PHTR_BUILD_TESTAPP)
