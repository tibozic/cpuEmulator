#include "test.h"

void test_lda_im(int *failed, CPU *cpu, MEMORY *memory)
{
	printf("---- Running test_lda_im...\n");

	reset_cpu(cpu, memory);
	memory->data[0xFFFC] = INS_LDA_IM;
	memory->data[0xFFFD] = 0x12;
	int number_of_instructions_used = execute_instruction(cpu, memory);

	if (cpu->a == 0x12 && number_of_instructions_used == 2)
	{
		printf("Test passed!\n");
	}
	else
	{
		(*failed)++;
		printf("Test failed!\n");
	}
}
