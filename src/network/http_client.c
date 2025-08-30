//
// Created by Mitchell on 8/26/2025.
//

#include <curl/curl.h>
#include "http_client.h"

size_t write_callback(char *ptr, size_t size, size_t nmemb, void *userdata) {
    ResponseBuffer* response_buffer = userdata;
    const size_t new_memory = size * nmemb;
    if (new_memory + response_buffer->data_amount > response_buffer->capacity) {
        const size_t new_capacity = response_buffer->capacity * (size_t)2;
        char* new_buffer = realloc(response_buffer->buffer, new_capacity);
        if (!new_buffer) {
            return 0;
        }
        response_buffer->buffer = new_buffer;
        response_buffer->capacity = new_capacity;
    }
    memcpy(response_buffer->buffer + response_buffer->data_amount, ptr, new_memory);
    response_buffer->data_amount = response_buffer->data_amount + new_memory;
    return new_memory;
}

int fetch_stock_data(Config* config, char tickers[][10], const int ticker_count, char** json_response) {
    CURL *curl = curl_easy_init();
    ResponseBuffer buffer[ticker_count];
    if (curl) {
        char full_url[256];

        for (int i = 0; i < ticker_count; i++) {
            buffer[i].capacity = 1024;
            buffer[i].buffer = (char*)malloc(buffer[i].capacity);
            buffer[i].data_amount = 0;

            snprintf(full_url, sizeof(full_url),
            "%s/%s/prev?apikey=%s",
            config->base_url, tickers[i], config->api_key);

            curl_easy_setopt(curl, CURLOPT_URL, full_url);
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer[i]);

            CURLcode res = curl_easy_perform(curl);
            if (res != CURLE_OK) {
                for (int j = 0; j <= i; j++) {
                    free(buffer[j].buffer);
                }
                return -1;
            }
            buffer[i].buffer[buffer[i].data_amount] = '\0';
            json_response[i] = buffer[i].buffer;

        }
        curl_easy_cleanup(curl);
    }
    else {
        return -1;
    }
    return 0;
}