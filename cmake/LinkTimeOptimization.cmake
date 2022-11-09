# Interprocedural Optimization (LTO)

cmake_policy(SET CMP0069 NEW)
include(CheckIPOSupported) # fails if policy 69 is not set

check_ipo_supported(RESULT ipo_found OUTPUT ipo_output)

if(NOT ipo_found)
  message(WARNING "Link Time Optimization not supported: ${ipo_output}")
elseif(Bresenham_USE_CLANG_TIDY)
  message(STATUS "Disabling Link Time Optimization because of clang-tidy")
else()
  message(STATUS "Link Time Optimization enabled")

  if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    # avoid error when mixing clang 10 lto and ld:
    # /usr/bin/ld: lib<>.a: error adding symbols: file format not recognized
    message(STATUS "Use lld")
    add_link_options("-fuse-ld=lld")
  endif()

  # Either set LTO globally
  option(CMAKE_INTERPROCEDURAL_OPTIMIZATION "Link Time Optimization" ON)

  # or set it on a target basis
  # set_property(TARGET ${TARGET_NAME} PROPERTY INTERPROCEDURAL_OPTIMIZATION TRUE)

endif()