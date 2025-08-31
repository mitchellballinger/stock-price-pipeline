//
// Created by Mitchell on 8/31/2025.
//

#include "../unity/unity.h"
#include "../../src/core/stock_parser.h"

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

void test_parse_invalid_json(void) {
    const char* invalid_json = "{invalid json}";
    StockDataPoint stock_data;

    int result = parse_stock_data(invalid_json, &stock_data);
    TEST_ASSERT_NOT_EQUAL(0, result); // Should return error code
}

void test_parse_empty_json(void) {
    const char* empty_json = "";
    StockDataPoint stock_data;

    int result = parse_stock_data(empty_json, &stock_data);
    TEST_ASSERT_NOT_EQUAL(0, result);
}

void test_parse_extreme_values(void) {
    // Very large numbers
    const char* json = "{\"results\":[{\"T\":\"AAPL\",\"c\":999999.99,\"v\":1000000,\"t\":1756497600000}]}";
    StockDataPoint stock_data;

    int result = parse_stock_data(json, &stock_data);
    TEST_ASSERT_EQUAL(0, result);
    TEST_ASSERT_DOUBLE_WITHIN(0.01, 999999.99, stock_data.price);
}

void test_parse_zero_values(void) {
    const char* json = "{\"results\":[{\"T\":\"AAPL\",\"c\":0.0,\"v\":0,\"t\":0}]}";
    StockDataPoint stock_data;

    int result = parse_stock_data(json, &stock_data);
    // Decide if zero values are valid for your use case
    TEST_ASSERT_EQUAL(0, result);
    TEST_ASSERT_DOUBLE_WITHIN(0.0001, 0.0, stock_data.price);
}

void test_parse_empty_results_array(void) {
    const char* json = "{\"results\":[]}";
    StockDataPoint stock_data;

    int result = parse_stock_data(json, &stock_data);
    TEST_ASSERT_NOT_EQUAL(0, result); // Should indicate no data
}

int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_parse_valid_json);
    RUN_TEST(test_parse_invalid_json);
    RUN_TEST(test_parse_empty_json);

    RUN_TEST(test_parse_extreme_values);
    RUN_TEST(test_parse_zero_values);

    RUN_TEST(test_parse_empty_results_array);
    return UNITY_END();
}