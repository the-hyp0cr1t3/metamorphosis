message(status "in examples")

#---------------------------
# Define targets
#---------------------------
add_executable(Bresenham_example_main main.cpp)
add_executable(Bresenham::Bresenham_example_main ALIAS Bresenham_example_main)
set_target_properties(Bresenham_example_main PROPERTIES OUTPUT_NAME main)
target_link_libraries(Bresenham_example_main Bresenham::bresenham glfw glad ${CMAKE_DL_LIBS})

add_custom_target(frames ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/frames
    $<TARGET_FILE_DIR:Bresenham_example_main>/frames
    DEPENDS ${Bresenham_example_main})

#---------------------------
# Install
#---------------------------
install(
  TARGETS Bresenham_example_main
  EXPORT Bresenham
  DESTINATION ${CMAKE_INSTALL_BINDIR}
  COMPONENT Bresenham_Development)