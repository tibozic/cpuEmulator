#include "test.h"

int main(void)
{
	CPU cpu;
	MEMORY memory;

	return run_all_tests(&cpu, &memory);
}
