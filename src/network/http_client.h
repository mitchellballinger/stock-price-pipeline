//
// Created by Mitchell on 8/26/2025.
//

#ifndef STOCK_PIPELINE_HTTP_CLIENT_H
#define STOCK_PIPELINE_HTTP_CLIENT_H
#include "../core/config.h"

typedef struct {
    char* buffer;
    size_t data_amount;
    size_t capacity;
} ResponseBuffer;

size_t write_callback(char *ptr, size_t size, size_t nmemb, void *userdata);

int fetch_stock_data(Config* config, char tickers[][10], const int ticker_count, char** json_response);


#endif //STOCK_PIPELINE_HTTP_CLIENT_H