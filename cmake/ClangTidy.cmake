if(Bresenham_USE_CLANG_TIDY)

  if(CMAKE_VERSION VERSION_GREATER 3.6)

    find_program(CLANG_TIDY_EXE NAMES "clang-tidy")

    if(CLANG_TIDY_EXE)
      message(STATUS "Found clang-tidy: ${CLANG_TIDY_EXE}")
      set(CMAKE_CXX_CLANG_TIDY
          "${CLANG_TIDY_EXE};--header-filter=${CMAKE_CURRENT_SOURCE_DIR}/include/*"
      )

    else()
      message(SEND_ERROR "clang-tidy executable not found")

    endif()

  else()
    message(
      SEND_ERROR
        "clang-tidy was requested, but cmake is too old, 3.6 or greater is required"
    )

  endif()

endif()

# To auto fix, set CMAKE_EXPORT_COMPILE_COMMANDS=ON and run clang-tidy --fix
# -p=build <source0> [... <sourceN>]
