#include "cpu.h"

int main(void)
{
	CPU cpu;
	MEMORY memory;

	reset_cpu(&cpu, &memory);

	/* Start of simple test program */
	{
		cpu.x = 0x04;
		memory.data[0xFFFC] = INS_LDA_ABSX;
		memory.data[0xFFFD] = 0x42;
		memory.data[0xFFFE] = 0x42;
		memory.data[0x4246] = 0x64;
		execute_instruction(5, &cpu, &memory);
	}
	/* End of simple test program */

	printf("Value of A: 0x%x\n", cpu.a);

	return 0;
}
