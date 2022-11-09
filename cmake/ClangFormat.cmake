set(patterns "")

foreach(dir IN ITEMS src include tests examples)
  list(APPEND patterns
    ${dir}/*.cpp
    ${dir}/*.cxx
    ${dir}/*.cc
    ${dir}/*.hpp
    ${dir}/*.hxx
    ${dir}/*.h)
endforeach()

set(FORMAT_PATTERNS
    ${patterns}
    CACHE STRING
          "; separated patterns relative to the project source dir to format")

set(FORMAT_COMMAND clang-format CACHE STRING "Formatter to use")

add_custom_target(
  format-check
  COMMAND "${CMAKE_COMMAND}"
    -D "FORMAT_COMMAND=${FORMAT_COMMAND}"
    -D "PATTERNS=${FORMAT_PATTERNS}"
    -P "${PROJECT_SOURCE_DIR}/cmake/lint.cmake"
  WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}"
  COMMENT "Linting the code"
  VERBATIM)

add_custom_target(
  format-fix
  COMMAND "${CMAKE_COMMAND}"
    -D FIX=YES
    -D "FORMAT_COMMAND=${FORMAT_COMMAND}"
    -D "PATTERNS=${FORMAT_PATTERNS}"
    -P "${PROJECT_SOURCE_DIR}/cmake/lint.cmake"
  WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}"
  COMMENT "Fixing the code"
  VERBATIM)
