//
// Created by Mitchell on 8/30/2025.
//

#include "csv_writer.h"

#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>

/**
 * Writes the stock data to csv
 */
int write_stock_data_to_csv(const char* filename, StockDataPoint* stock_data_array, int count) {
    bool file_exists = (access(filename, F_OK) == 0);
    FILE *fptr;
    fptr = fopen(filename, "a");
    if (!fptr) return -1;
    if (!file_exists) {
        fprintf(fptr, "timestamp,ticker,price,volume\n");
    }
    for (int i = 0; i < count; i++) {
        struct tm *tm_info = localtime(&stock_data_array[i].timestamp);
        char date_string[20];
        strftime(date_string, sizeof(date_string), "%Y-%m-%d", tm_info);
        fprintf(fptr, "%s,%s,%.2f,%lu\n", date_string, stock_data_array[i].ticker,
            stock_data_array[i].price, stock_data_array[i].volume);
    }

    fclose(fptr);
    return 0;
}
