add_library(bressenham bressenham.cpp drawCircle.cpp drawLine.cpp)
  target_include_directories(bressenham PUBLIC ${PROJECT_SOURCE_DIR}/include)
  target_link_libraries(bressenham PUBLIC glad)