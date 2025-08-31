//
// Created by Mitchell on 8/27/2025.
//

#include "stock_parser.h"
#include <cjson/cJSON.h>
#include <stdint.h>
#include <string.h>

int parse_stock_data(const char* json_string, StockDataPoint* stock_data) {
    cJSON *root = cJSON_Parse(json_string);
    if (!root) return -1;
    cJSON *results = cJSON_GetObjectItem(root, "results");
    if (!results) { cJSON_Delete(root); return -1; }
    cJSON *first_result = cJSON_GetArrayItem(results, 0);
    if (!first_result) { cJSON_Delete(root); return -1; }
    char *ticker = cJSON_GetObjectItem(first_result, "T")->valuestring;
    if (!ticker) { cJSON_Delete(root); return -1; }
    double close_price = cJSON_GetObjectItem(first_result, "c")->valuedouble;
    unsigned long volume = (unsigned long)cJSON_GetObjectItem(first_result, "v")->valuedouble;
    uint64_t timestamp = (uint64_t)cJSON_GetObjectItem(first_result, "t")->valuedouble;
    timestamp /= 1000;
    time_t converted_timestamp = (time_t)timestamp;

    strcpy(stock_data->ticker, ticker);
    stock_data->price = close_price;
    stock_data->volume = volume;
    stock_data->timestamp = converted_timestamp;

    cJSON_Delete(root);
    return 0;
}
