add_library(rmc STATIC rmc.cpp)
target_include_directories(rmc PRIVATE ${CMAKE_SOURCE_DIR}/includes)
