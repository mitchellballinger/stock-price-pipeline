add_executable(test_parser
        unity/unity.c
        unit/test_parser.c
        ../src/core/stock_parser.c
)

target_include_directories(test_parser PRIVATE ../src/core unity)
target_link_libraries(test_parser PRIVATE cjson)