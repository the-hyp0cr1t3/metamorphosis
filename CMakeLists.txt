cmake_minimum_required(VERSION 3.20)
project(RasterizationAlgos CXX C)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

if(MSVC)
  SET( CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /ENTRY:mainCRTStartup" )
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})

add_subdirectory(extern)

add_subdirectory(src)

add_subdirectory(examples)