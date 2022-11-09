include(FetchContent)

find_package(glfw3 3.3.8 CONFIG QUIET)

if(NOT glfw3_FOUND)
  message(STATUS "GLFW not installed, downloading...")

  FetchContent_Declare(
    glfw3
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG 3.3.8
    GIT_PROGRESS TRUE
  )

  option(GLFW_BUILD_DOCS OFF)
  option(GLFW_BUILD_EXAMPLES OFF)
  option(GLFW_BUILD_TESTS OFF)

  set(FETCHCONTENT_QUIET NO)
  FetchContent_MakeAvailable(glfw3)

else()
  message(STATUS "Found GLFW: " ${glfw3_DIR})

endif()

add_subdirectory(glad)