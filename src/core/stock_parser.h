//
// Created by Mitchell on 8/27/2025.
//

#ifndef STOCK_PIPELINE_STOCK_PARSER_H
#define STOCK_PIPELINE_STOCK_PARSER_H
#include "stock_data.h"

/**
 * Module for parsing stock data
 */


/**
 * Parses stock data from API call
 * @param json_string
 * @param stock_data
 * @return
 */
int parse_stock_data(const char* json_string, StockDataPoint* stock_data);

#endif //STOCK_PIPELINE_STOCK_PARSER_H