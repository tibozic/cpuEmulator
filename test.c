#include "test.h"

#define EXPECT_EQUAL(...) expect_equal(__FUNCTION__, __VA_ARGS__)

void expect_equal(const char *function_name, int value1, int value2);

int run_all_tests(CPU *cpu, MEMORY *memory)
{
	int failed = 0;
	int num_of_tests = 0;

	test_lda_im(&num_of_tests, &failed, cpu, memory);


	printf("**** ");
	printf("Ran %d tests, %d passed, %d failed.\n",
		   num_of_tests,
		   (num_of_tests - failed),
		   failed);

	return failed;
}

void test_lda_im(int *num_of_tests, int *failed, CPU *cpu, MEMORY *memory)
{
	printf("---- Running test_lda_im...\n");
	(*num_of_tests)++;

	reset_cpu(cpu, memory);
	memory->data[0xFFFC] = INS_LDA_IM;
	memory->data[0xFFFD] = 0x12;
	int number_of_instructions_used = execute_instruction(cpu, memory);

	EXPECT_EQUAL(cpu->a, 0x12);
	EXPECT_EQUAL(number_of_instructions_used, 2);
}

void expect_equal(const char *function_name, int value1, int value2)
{
	if (value1 == value2)
	{
		fprintf(stdout,
				"[ " ANSI_COLOR_GREEN " Passed " ANSI_COLOR_RESET " ] %s\n",
				function_name);
	}
	else
	{
		fprintf(stderr,
				"[ " ANSI_COLOR_RED " Failed " ANSI_COLOR_RESET " ] %s\n",
				function_name);
	}
}
