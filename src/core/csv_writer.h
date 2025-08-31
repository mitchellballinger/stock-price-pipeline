//
// Created by Mitchell on 8/30/2025.
//

#ifndef STOCK_PIPELINE_CSV_WRITER_H
#define STOCK_PIPELINE_CSV_WRITER_H
#include "stock_data.h"

/**
 * Module for creating and writing to csv file that will hold stock data
*/


/**
 * Writes the stock data to a csv file
 * @param filename, name of csv file to write to
 * @param stock_data_array, array of stock data points
 * @param count, amount of stocks that were parsed
 * @return integer indicating success or failure
 */
int write_stock_data_to_csv(const char* filename, StockDataPoint* stock_data_array, int count);


#endif //STOCK_PIPELINE_CSV_WRITER_H