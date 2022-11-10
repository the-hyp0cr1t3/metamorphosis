message(status "in examples")

#---------------------------
# Define targets
#---------------------------
add_executable(Bresenham_example_main main.cpp)
add_executable(Bresenham::Bresenham_example_main ALIAS Bresenham_example_main)
set_target_properties(Bresenham_example_main PROPERTIES OUTPUT_NAME main)
target_link_libraries(Bresenham_example_main Bresenham::bresenham glfw glad ${CMAKE_DL_LIBS})

add_custom_command(
	TARGET Bresenham_example_main POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_directory
		"${PROJECT_SOURCE_DIR}/frames"
		"${PROJECT_BINARY_DIR}/bin/frames"
)

#---------------------------
# Install
#---------------------------
install(
  TARGETS Bresenham_example_main
  EXPORT Bresenham
  DESTINATION ${CMAKE_INSTALL_BINDIR}
  COMPONENT Bresenham_Development)