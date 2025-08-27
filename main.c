
#include "config.h"
#include "http_client.h"
#include "stock_data.h"

int main() {
    Config *config = load_config();
    char tickers[5][10];

    const int ticker_count = read_stock_tickers(tickers);

    fetch_stock_data(config, tickers, ticker_count);

    return 0;
}