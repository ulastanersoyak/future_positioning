add_library(utm STATIC utm.cpp)
target_link_libraries(utm rmc time_and_location)
target_include_directories(utm PRIVATE ${CMAKE_SOURCE_DIR}/includes/)
