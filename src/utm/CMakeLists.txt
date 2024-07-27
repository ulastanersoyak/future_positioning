add_library(utm STATIC utm.cpp)
target_include_directories(utm PRIVATE ${CMAKE_SOURCE_DIR}/includes/)
