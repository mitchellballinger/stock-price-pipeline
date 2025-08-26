#include <stdio.h>
#include <string.h>
#include <time.h>

typedef struct StockDataPoint {
    double price;
    unsigned long volume;
    time_t timestamp;
    char ticker[10];
} StockDataPoint;

int read_stock_tickers(char tickers[5][10]) {
    char buffer[10];
    FILE *fptr = fopen("stocks.txt", "r");
    if (fptr != NULL) {

        const int size = 10;
        int count = 0;
        while (fgets(buffer, size, fptr) != NULL && count < 5) {

            char *newline_pos = strchr(buffer, '\n');
            if (newline_pos != NULL) {
                *newline_pos = '\0';
            }

            strcpy(tickers[count], buffer);

            count++;
        }
        fclose(fptr);
        return count;
    }
    return 0;
};

int main() {

    char tickers[5][10];
    const int count = read_stock_tickers(tickers);
    for (int i = 0; i < count; i++) {
        printf("Tickers[%d] = %s\n", i, tickers[i]);
    }
    return 0;
}