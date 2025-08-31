
#include <stdio.h>
#include <stdlib.h>

#include "config.h"
#include "csv_writer.h"
#include "../network/http_client.h"
#include "stock_data.h"
#include "stock_parser.h"

int main() {
    Config *config = load_config();
    char tickers[5][10];

    const int ticker_count = read_stock_tickers(tickers);
    char** json_response_data = malloc(ticker_count * sizeof(char*));
    const int status = fetch_stock_data(config, tickers, ticker_count, json_response_data);

    if (status == 0) {
        StockDataPoint stock_data_array[ticker_count];
        int successful_count = 0;
        for (int i = 0; i < ticker_count; i++) {
            int result = parse_stock_data(json_response_data[i], &stock_data_array[i]);
            if (result == 0) {
                successful_count++;
            } else {
                printf("Failed to parse JSON for ticker %d\n", i);
            }
        }
        if (successful_count > 0) {
            write_stock_data_to_csv("stock_data.csv", stock_data_array, successful_count);
        }
    }
    else {
        printf("Error reading config file\n");
    }

    free(json_response_data);

    return 0;
}