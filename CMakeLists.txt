cmake_minimum_required(VERSION 3.10)
project(stock_pipeline)

set(CMAKE_C_STANDARD 99)

# Create a library with your core functionality
add_library(stock_core
        src/core/config.c
        src/core/stock_data.c
        src/core/stock_parser.c
        src/core/csv_writer.c
        src/network/http_client.c
)

target_include_directories(stock_core PUBLIC src/core src/network)

# Main executable
add_executable(main src/core/main.c)
target_link_libraries(main PRIVATE stock_core)

# Find packages
find_package(CURL REQUIRED)

if(WIN32)
    find_package(CJSON REQUIRED)
    target_link_libraries(stock_core PRIVATE CURL::libcurl cjson)
else()
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(CJSON REQUIRED libcjson)
    target_link_libraries(stock_core PRIVATE CURL::libcurl ${CJSON_LIBRARIES})
    target_include_directories(stock_core PRIVATE ${CJSON_INCLUDE_DIRS})
endif()

target_link_libraries(main PRIVATE stock_core)

add_subdirectory(tests)