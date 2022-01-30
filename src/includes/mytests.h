#ifndef MYTESTS_H_
#define MYTESTS_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define START_TEST(...) start_test(__FUNCTION__, __VA_ARGS__)
#define END_TEST() end_test(__FUNCTION__)
#define EXPECT_EQ(...) expect_eq(__FUNCTION__, __LINE__, __VA_ARGS__)
#define EXPECT_NEQ(...) expect_neq(__FUNCTION__, __LINE__,  __VA_ARGS__)
#define EXPECT_TRUE(...) expect_true(__FUNCTION__, __LINE__, __VA_ARGS__)
#define EXPECT_FALSE(...) expect_false(__FUNCTION__, __LINE__, __VA_ARGS__)

// ANSI color codes
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

void start_test(const char *function_name, const char *section_name);
void end_test(const char *function_name);
void expect_eq(const char *function_name, int line_number, int value1, int value2);
void expect_neq(const char *function_name, int line_number, int value1, int value2);
void expect_true(const char *function_name, int line_number, bool value);
void expect_false(const char *function_name, int line_number, bool value);
void print_report();

#endif // MYTESTS_H_
