cmake_minimum_required(VERSION 3.10)
project(stock_pipeline)

set(CMAKE_C_STANDARD 99)

add_executable(main src/core/main.c
        src/core/config.h
        src/core/config.c
        src/core/stock_data.h
        src/core/stock_data.c
        src/network/http_client.c
        src/network/http_client.h
        src/core/stock_parser.c
        src/core/stock_parser.h)

find_package(CURL REQUIRED)
find_package(CJSON REQUIRED)
target_link_libraries(main PRIVATE CURL::libcurl cjson)