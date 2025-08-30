
#include <stdio.h>
#include <stdlib.h>

#include "config.h"
#include "../network/http_client.h"
#include "stock_data.h"

int main() {
    Config *config = load_config();
    char tickers[5][10];

    const int ticker_count = read_stock_tickers(tickers);
    char** json_response_data = malloc(ticker_count * sizeof(char*));
    const int status = fetch_stock_data(config, tickers, ticker_count, json_response_data);

    if (status !=0) {
        printf("Error reading config file\n");
    }
    else {
        printf(*json_response_data);
    }

    return 0;
}