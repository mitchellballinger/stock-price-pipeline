cmake_minimum_required(VERSION 3.10)
project(stock_pipeline)

set(CMAKE_C_STANDARD 99)

add_executable(main main.c
        config.h
        config.c
        stock_data.h
        stock_data.c
        http_client.c
        http_client.h)

find_package(CURL REQUIRED)
target_link_libraries(main PRIVATE CURL::libcurl)