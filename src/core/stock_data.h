//
// Created by Mitchell on 8/26/2025.
//

#ifndef STOCK_PIPELINE_STOCK_DATA_H
#define STOCK_PIPELINE_STOCK_DATA_H
#include <time.h>

/**
 * Creates StockDataPoint struct to hold stock data, and
 * retrieves stock tickers from txt file
 */


typedef struct StockDataPoint {
    double price;
    unsigned long volume;
    time_t timestamp;
    char ticker[10];
} StockDataPoint;

/**
 * Reads all stock tickers from csv file
 * @param tickers Array of tickers from the text file, update first index when increasing amt of stocks
 * @return integer determining success or failure
 */
int read_stock_tickers(char tickers[5][10]);


#endif //STOCK_PIPELINE_STOCK_DATA_H