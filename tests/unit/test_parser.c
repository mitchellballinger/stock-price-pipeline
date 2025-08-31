//
// Created by Mitchell on 8/31/2025.
//

#include "../unity/unity.h"
#include "../../src/core/stock_parser.h"
#include <string.h>

void setUp(void) {
    // Run before each test
}

void tearDown(void) {
    // Run after each test
}

void test_parse_valid_json(void) {
    const char* json = "{\"results\":[{\"T\":\"AAPL\",\"c\":150.15,\"v\":1000000,\"t\":1756497600000}]}";
    StockDataPoint stock_data;

    int result = parse_stock_data(json, &stock_data);

    TEST_ASSERT_EQUAL(0, result);
    TEST_ASSERT_EQUAL_STRING("AAPL", stock_data.ticker);
    TEST_ASSERT_DOUBLE_WITHIN(0.0001, 150.15, stock_data.price);
    TEST_ASSERT_EQUAL_UINT(1000000, stock_data.volume);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_parse_valid_json);
    return UNITY_END();
}