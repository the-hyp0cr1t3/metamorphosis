# ---------------------------
# Define targets
# ---------------------------
add_library(bresenham bresenham.cpp drawCircle.cpp drawLine.cpp drawEllipse.cpp)
add_library(Bresenham::bresenham ALIAS bresenham)

target_link_libraries(bresenham PUBLIC glad)
target_include_directories(bresenham
  PUBLIC "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>"
         "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>")

# ---------------------------
# Install
# ---------------------------
install(
  TARGETS bresenham
  EXPORT Bresenham
  RUNTIME
    DESTINATION "${CMAKE_INSTALL_BINDIR}"
    COMPONENT Bresenham_Runtime
  LIBRARY
    DESTINATION "${CMAKE_INSTALL_LIBDIR}"
    COMPONENT Bresenham_Runtime
    NAMELINK_COMPONENT Bresenham_Development
  ARCHIVE
    DESTINATION "${CMAKE_INSTALL_LIBDIR}"
    COMPONENT Bresenham_Development)
