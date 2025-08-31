# Parser tests
add_executable(test_parser
        Unity/unity.c
        unit/test_parser.c
)

# Reader tests
add_executable(test_reader
        Unity/unity.c
        unit/test_reader.c
)

target_link_libraries(test_parser PRIVATE stock_core)
target_link_libraries(test_reader PRIVATE stock_core)

target_include_directories(test_parser PRIVATE Unity)
target_include_directories(test_reader PRIVATE Unity)