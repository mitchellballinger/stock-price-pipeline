//
// Created by Mitchell on 8/30/2025.
//

#ifndef STOCK_PIPELINE_CSV_WRITER_H
#define STOCK_PIPELINE_CSV_WRITER_H
#include "stock_data.h"

int write_stock_data_to_csv(const char* filename, StockDataPoint* stock_data_array, int count);


#endif //STOCK_PIPELINE_CSV_WRITER_H