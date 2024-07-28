add_subdirectory(time_and_location)
add_subdirectory(rmc)
add_subdirectory(utm)
add_subdirectory(gps)

add_executable(main main.cpp)
target_link_libraries(main rmc time_and_location utm gps)
target_include_directories(main PRIVATE ${CMAKE_SOURCE_DIR}/includes/)
