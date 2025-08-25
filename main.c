#include <stdio.h>
#include <string.h>

typedef struct StockDataPoint {
    double price;
    unsigned long volume;
    time_t timestamp;
    char ticker[10];
} StockDataPoint;

int main() {

    StockDataPoint data;
    char tickers[5][10];
    char buffer[10];
    FILE *fptr = fopen("StockData.txt", "r");
    if (fptr != NULL) {

        const int size = 10;
        int i = 0;
        while (fgets(buffer, size, fptr) != NULL && i < 5) {

            char *newline_pos = strchr(buffer, '\n');
            if (newline_pos != NULL) {
                *newline_pos = '\0';
            }

            strcpy(tickers[i], buffer);

            i++;
        }
    }



    fclose(fptr);

    printf("Hello, Stock Pipeline!\n");
    return 0;
}