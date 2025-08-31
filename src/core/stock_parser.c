//
// Created by Mitchell on 8/27/2025.
//

#include "stock_parser.h"
#include <cjson/cJSON.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Parse the stock data that is returned from the API call,
 * Manually parses the timestamp because cJSON cannot hold large integers
 */
int parse_stock_data(const char* json_string, StockDataPoint* stock_data) {
    if (json_string == NULL) {
        return -1;
    }
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

    // Find the timestamp in the raw JSON string
    // Have to manually parse for the timestamp string since cJSON can't handle large numbers
    const char *t_pos = strstr(json_string, "\"t\":");
    if (!t_pos) {
        cJSON_Delete(root);
        return -1;  // timestamp field not found
    }

    t_pos += 4; // Skip past "t":
    while (*t_pos == ' ' || *t_pos == '\t') t_pos++; // Skip whitespace

    uint64_t timestamp = strtoull(t_pos, NULL, 10);
    timestamp /= 1000;
    time_t converted_timestamp = (time_t)timestamp;

    strcpy(stock_data->ticker, ticker);
    stock_data->price = close_price;
    stock_data->volume = volume;
    stock_data->timestamp = converted_timestamp;

    cJSON_Delete(root);
    return 0;
}
