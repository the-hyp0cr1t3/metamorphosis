include(CMakeDependentOption)

if(PROJECT_IS_TOP_LEVEL)

  option(BUILD_SHARED_LIBS "Build libraries as shared as opposed to static" OFF)

  # Developer mode enables targets and code paths in the CMake scripts that are
  # only relevant for the developer(s)
  # Targets necessary to build the project must be provided unconditionally, so
  # consumers can trivially build and package the project
  option(Bresenham_DEVELOPER_MODE "Enable developer mode" OFF)

  option(Bresenham_BUILD_DOCS "Build documentation using Doxygen and m.css" ON)

  option(Bresenham_BUILD_EXAMPLES "Build example programs" ON)

  cmake_dependent_option(
    Bresenham_USE_CLANG_TIDY
    "Run clang-tidy on sources" ON
    "Bresenham_DEVELOPER_MODE" OFF)

  foreach(var IN ITEMS
            Bresenham_DEVELOPER_MODE
            Bresenham_BUILD_DOCS
            Bresenham_BUILD_EXAMPLES
            Bresenham_USE_CLANG_TIDY)

    message(STATUS "${var}=${${var}}")

  endforeach()

endif()