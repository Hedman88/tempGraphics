cmake_minimum_required(VERSION 3.18)

ADD_EXECUTABLE(app main.cc)
target_link_libraries(app pthread)
