//
// Created by Mitchell on 8/26/2025.
//

#ifndef STOCK_PIPELINE_HTTP_CLIENT_H
#define STOCK_PIPELINE_HTTP_CLIENT_H
#include "../core/config.h"


/**
 * Module retrieves and stores the response from the financial API
 */
typedef struct {
    char* buffer;
    size_t data_amount;
    size_t capacity;
} ResponseBuffer;

/**
 * libcurl write callback function for accumulating HTTP response data
 *
 * Called by libcurl multiple times as data arrives from the server.
 * Accumulates chunks into a growing buffer, resizing as needed.
 *
 * @param ptr Pointer to received data chunk
 * @param size Size of each element (usually 1)
 * @param nmemb Number of elements received
 * @param userdata Pointer to ResponseBuffer structure for storing data
 * @return Number of bytes processed (size * nmemb on success, 0 on error)
 */
size_t write_callback(char *ptr, size_t size, size_t nmemb, void *userdata);

/**
 * Fetches stock market data from Polygon.io API for multiple tickers
 *
 * Makes HTTP requests to retrieve previous day's stock data for each ticker.
 * Allocates memory for JSON responses which must be freed by caller.
 *
 * @param config Configuration containing API key and base URL
 * @param tickers 2D array of ticker symbols (max 10 chars each)
 * @param ticker_count Number of tickers to fetch
 * @param json_response Array of string pointers to store JSON responses
 * @return 0 on success, -1 on failure (curl init failure or HTTP error)
 *
 * Note: Caller must free each json_response[i] and the json_response array itself
 */
int fetch_stock_data(Config* config, char tickers[][10], const int ticker_count, char** json_response);


#endif //STOCK_PIPELINE_HTTP_CLIENT_H