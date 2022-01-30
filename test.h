#ifndef TEST_H_
#define TEST_H_

#include <stdio.h>

#include "cpu.h"

// ANSI color codes
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

// Functions
int run_all_tests(CPU *cpu, MEMORY *memory);
void test_lda_im(int *num_of_tests, int *failed, CPU *cpu, MEMORY *memory);

#endif // TEST_H_
