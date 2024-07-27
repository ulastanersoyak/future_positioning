add_executable(tests test.cpp)
target_include_directories(tests PRIVATE ${CMAKE_SOURCE_DIR}/includes)
target_link_libraries(tests time_and_location rmc)
