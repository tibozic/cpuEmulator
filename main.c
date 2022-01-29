#include "test.h"

int main(void)
{
	CPU cpu;
	MEMORY memory;

	int failed = 0;

	test_lda_im(&failed, &cpu, &memory);

	return 0;
}
