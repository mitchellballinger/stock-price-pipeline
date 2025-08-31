//
// Test file for stock ticker reader
//

#include "../unity/unity.h"
#include "../../src/core/stock_data.h"  // Adjust path as needed
#include <stdio.h>
#include <string.h>

// Test file names
#define TEST_FILE_VALID "test_stocks_valid.txt"
#define TEST_FILE_EMPTY "test_stocks_empty.txt"
#define TEST_FILE_LONG_LINES "test_stocks_long.txt"
#define TEST_FILE_THREE_TICKERS "test_stocks_three.txt"

void setUp(void) {
    // Clean up any existing test files
    remove(TEST_FILE_VALID);
    remove(TEST_FILE_EMPTY);
    remove(TEST_FILE_LONG_LINES);
    remove(TEST_FILE_THREE_TICKERS);
}

void tearDown(void) {
    // Clean up test files after each test
    remove(TEST_FILE_VALID);
    remove(TEST_FILE_EMPTY);
    remove(TEST_FILE_LONG_LINES);
    remove(TEST_FILE_THREE_TICKERS);
}

// Helper function to create test files
void create_test_file(const char* filename, const char* content) {
    FILE* file = fopen(filename, "w");
    if (file) {
        fputs(content, file);
        fclose(file);
    }
}

void test_read_valid_stock_file(void) {
    // Create a test file with 5 valid tickers
    create_test_file(TEST_FILE_VALID, "AAPL\nMSFT\nGOOGL\nTSLA\nAMZN\n");

    // Temporarily rename the test file to stocks.txt for the function
    rename(TEST_FILE_VALID, "stocks.txt");

    char tickers[5][10];
    int result = read_stock_tickers(tickers);

    // Rename back
    rename("stocks.txt", TEST_FILE_VALID);

    TEST_ASSERT_EQUAL(5, result);
    TEST_ASSERT_EQUAL_STRING("AAPL", tickers[0]);
    TEST_ASSERT_EQUAL_STRING("MSFT", tickers[1]);
    TEST_ASSERT_EQUAL_STRING("GOOGL", tickers[2]);
    TEST_ASSERT_EQUAL_STRING("TSLA", tickers[3]);
    TEST_ASSERT_EQUAL_STRING("AMZN", tickers[4]);
}

void test_read_fewer_than_five_tickers(void) {
    // Create a test file with only 3 tickers
    create_test_file(TEST_FILE_THREE_TICKERS, "AAPL\nMSFT\nGOOGL\n");

    rename(TEST_FILE_THREE_TICKERS, "stocks.txt");

    char tickers[5][10];
    int result = read_stock_tickers(tickers);

    rename("stocks.txt", TEST_FILE_THREE_TICKERS);

    TEST_ASSERT_EQUAL(3, result);
    TEST_ASSERT_EQUAL_STRING("AAPL", tickers[0]);
    TEST_ASSERT_EQUAL_STRING("MSFT", tickers[1]);
    TEST_ASSERT_EQUAL_STRING("GOOGL", tickers[2]);
}

void test_read_empty_file(void) {
    // Create an empty test file
    create_test_file(TEST_FILE_EMPTY, "");

    rename(TEST_FILE_EMPTY, "stocks.txt");

    char tickers[5][10];
    int result = read_stock_tickers(tickers);

    rename("stocks.txt", TEST_FILE_EMPTY);

    TEST_ASSERT_EQUAL(0, result);
}

void test_read_file_not_found(void) {
    // Make sure stocks.txt doesn't exist
    remove("stocks.txt");

    char tickers[5][10];
    int result = read_stock_tickers(tickers);

    TEST_ASSERT_EQUAL(0, result);
}

void test_read_file_with_more_than_five_tickers(void) {
    // Create file with 7 tickers, should only read first 5
    create_test_file("test_stocks_seven.txt", "AAPL\nMSFT\nGOOGL\nTSLA\nAMZN\nNVDA\nMETA\n");

    rename("test_stocks_seven.txt", "stocks.txt");

    char tickers[5][10];
    int result = read_stock_tickers(tickers);

    rename("stocks.txt", "test_stocks_seven.txt");
    remove("test_stocks_seven.txt");

    TEST_ASSERT_EQUAL(5, result);
    TEST_ASSERT_EQUAL_STRING("AAPL", tickers[0]);
    TEST_ASSERT_EQUAL_STRING("AMZN", tickers[4]);
}

void test_read_file_with_whitespace_and_empty_lines(void) {
    // Test file with extra whitespace
    create_test_file("test_stocks_whitespace.txt", "AAPL  \n\nMSFT\n  GOOGL\n\nTSLA\n");

    rename("test_stocks_whitespace.txt", "stocks.txt");

    char tickers[5][10];
    int result = read_stock_tickers(tickers);

    rename("stocks.txt", "test_stocks_whitespace.txt");
    remove("test_stocks_whitespace.txt");

    // This tests how your function handles whitespace and empty lines
    // The exact behavior depends on your implementation
    TEST_ASSERT_GREATER_THAN(0, result);
}

void test_tickers_array_not_modified_on_failure(void) {
    // Initialize tickers array with known values
    char tickers[5][10];
    strcpy(tickers[0], "INITIAL");
    strcpy(tickers[1], "VALUES");

    // Try to read from non-existent file
    remove("stocks.txt");
    int result = read_stock_tickers(tickers);

    TEST_ASSERT_EQUAL(0, result);
    // Verify that the function didn't modify the array on failure
    TEST_ASSERT_EQUAL_STRING("INITIAL", tickers[0]);
    TEST_ASSERT_EQUAL_STRING("VALUES", tickers[1]);
}

int main(void) {
    UNITY_BEGIN();

    // Happy path tests
    RUN_TEST(test_read_valid_stock_file);
    RUN_TEST(test_read_fewer_than_five_tickers);
    RUN_TEST(test_read_file_with_more_than_five_tickers);

    // Error handling tests
    RUN_TEST(test_read_file_not_found);
    RUN_TEST(test_read_empty_file);

    // Edge case tests
    RUN_TEST(test_read_file_with_whitespace_and_empty_lines);
    RUN_TEST(test_tickers_array_not_modified_on_failure);

    return UNITY_END();
}