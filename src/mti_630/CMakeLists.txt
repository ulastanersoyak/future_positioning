add_library(mti_630 STATIC data_packet_parser.cpp xbus_packet.cpp mti_630.cpp)
target_link_libraries(mti_630)
target_include_directories(mti_630 PRIVATE ${CMAKE_SOURCE_DIR}/includes)
