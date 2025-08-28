//
// Created by Mitchell on 8/26/2025.
//

#include <curl/curl.h>
#include "http_client.h"

void fetch_stock_data(Config* config, char tickers[][10], const int ticker_count) {
    CURL *curl = curl_easy_init();
    if (curl) {
        char full_url[256];

        for (int i = 0; i < ticker_count; i++) {

            snprintf(full_url, sizeof(full_url),
            "%s?function=GLOBAL_QUOTE&symbol=%s&apikey=%s",
            config->base_url, tickers[i], config->api_key);

            curl_easy_setopt(curl, CURLOPT_URL, full_url);

            CURLcode res = curl_easy_perform(curl);
        }
        curl_easy_cleanup(curl);
    }
}