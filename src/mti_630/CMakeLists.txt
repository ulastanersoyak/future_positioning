add_library(mti_630 STATIC mti_630.cpp mti_buffer.cpp)
target_include_directories(mti_630 PRIVATE ${CMAKE_SOURCE_DIR}/includes)
