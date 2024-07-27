add_library(time_and_location STATIC utc.cpp parser.cpp coordinate.cpp date.cpp)
target_include_directories(time_and_location PRIVATE ${CMAKE_SOURCE_DIR}/includes/)
