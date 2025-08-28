//
// Created by Mitchell on 8/26/2025.
//

#ifndef STOCK_PIPELINE_HTTP_CLIENT_H
#define STOCK_PIPELINE_HTTP_CLIENT_H
#include "../core/config.h"

void fetch_stock_data(Config* config, char tickers[][10], int ticker_count);


#endif //STOCK_PIPELINE_HTTP_CLIENT_H