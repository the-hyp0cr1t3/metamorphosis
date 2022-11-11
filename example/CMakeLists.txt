# ---------------------------
# Define targets
# ---------------------------
add_executable(Bresenham_render render.cpp)
add_executable(Bresenham::Bresenham_render ALIAS Bresenham_render)
set_target_properties(Bresenham_render PROPERTIES OUTPUT_NAME render)
target_link_libraries(Bresenham_render Bresenham::bresenham glfw glad
                      ${CMAKE_DL_LIBS})

add_custom_command(
  TARGET Bresenham_render
  POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_LIST_DIR}/frames
          $<TARGET_FILE_DIR:Bresenham_render>/frames)

# ---------------------------
# Install
# ---------------------------
install(
  TARGETS Bresenham_render
  EXPORT Bresenham
  DESTINATION ${CMAKE_INSTALL_BINDIR}
  COMPONENT Bresenham_Development)
