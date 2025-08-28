//
// Created by Mitchell on 8/26/2025.
//

#ifndef STOCK_PIPELINE_STOCK_DATA_H
#define STOCK_PIPELINE_STOCK_DATA_H
#include <time.h>

typedef struct StockDataPoint {
    double price;
    unsigned long volume;
    time_t timestamp;
    char ticker[10];
} StockDataPoint;

int read_stock_tickers(char tickers[5][10]);


#endif //STOCK_PIPELINE_STOCK_DATA_H