add_library(gps STATIC gps.cpp)
target_include_directories(gps PRIVATE ${CMAKE_SOURCE_DIR}/includes)
