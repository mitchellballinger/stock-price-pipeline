//
// Created by Mitchell on 8/26/2025.
//

#include <stdio.h>
#include <string.h>
#include "stock_data.h"

/**
 * Retrieves the stock tickers from stocks.txt file
 */
int read_stock_tickers(char tickers[5][10]) {
    char buffer[16];
    FILE *fptr = fopen("stocks.txt", "r");
    if (fptr != NULL) {

        int count = 0;
        while (fgets(buffer, sizeof(buffer), fptr) != NULL && count < 5) {

            buffer[strcspn(buffer, "\n")] = '\0';

            strcpy(tickers[count], buffer);

            count++;
        }
        fclose(fptr);
        return count;
    }
    return 0;
}