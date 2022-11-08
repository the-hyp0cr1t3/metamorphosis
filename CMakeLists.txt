cmake_minimum_required(VERSION 3.20)
project(RasterizationAlgos CXX C)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

if(MSVC)
  SET( CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /ENTRY:mainCRTStartup" )
endif()

add_subdirectory(extern)

add_subdirectory(examples)