#include "includes/mytests.h"
#include "cpu.h"

void test_lda_im(CPU cpu, MEMORY memory);
void test_lda_zp(CPU cpu, MEMORY memory);
void test_lda_zpx(CPU cpu, MEMORY memory);
void test_lda_abs(CPU cpu, MEMORY memory);
void test_lda_absx(CPU cpu, MEMORY memory);

int main(void)
{
	CPU cpu;
	MEMORY memory;

	test_lda_im(cpu, memory);
	test_lda_zp(cpu, memory);
	test_lda_zpx(cpu, memory);
	test_lda_abs(cpu, memory);
	test_lda_absx(cpu, memory);
	print_report();
}

void test_lda_im(CPU cpu, MEMORY memory)
{
	int number_of_instructions;

	START_TEST("LDA Immediate");

	reset_cpu(&cpu, &memory);
	memory.data[0xFFFC] = INS_LDA_IM;
	memory.data[0xFFFD] = 0x12;
	number_of_instructions = execute_instruction(&cpu, &memory);

	EXPECT_EQ(cpu.a, 0x12);
	EXPECT_EQ(number_of_instructions, 2);
	EXPECT_EQ(cpu.z, 0);
	EXPECT_EQ(cpu.n, 0);
	END_TEST();

	START_TEST("LDA Immediate - negative");

	reset_cpu(&cpu, &memory);
	memory.data[0xFFFC] = INS_LDA_IM;
	memory.data[0xFFFD] = 0x42;
	number_of_instructions = execute_instruction(&cpu, &memory);

	EXPECT_EQ(cpu.a, 0x42);
	EXPECT_EQ(number_of_instructions, 2);
	EXPECT_EQ(cpu.z, 0);
	EXPECT_EQ(cpu.n, 1);
	END_TEST();

	START_TEST("LDA Immediate - zero");

	reset_cpu(&cpu, &memory);
	memory.data[0xFFFC] = INS_LDA_IM;
	memory.data[0xFFFD] = 0x0;
	number_of_instructions = execute_instruction(&cpu, &memory);

	EXPECT_EQ(cpu.a, 0x0);
	EXPECT_EQ(number_of_instructions, 2);
	EXPECT_EQ(cpu.z, 1);
	EXPECT_EQ(cpu.n, 0);
	END_TEST();
}

void test_lda_zp(CPU cpu, MEMORY memory)
{
	int number_of_instructions;
	START_TEST("LDA Zero page");

	reset_cpu(&cpu, &memory);
	memory.data[0xFFFC] = INS_LDA_ZP;
	memory.data[0xFFFD] = 0x42;
	memory.data[0x42]	= 0x12;
	number_of_instructions = execute_instruction(&cpu, &memory);

	EXPECT_EQ(cpu.a, 0x12);
	EXPECT_EQ(number_of_instructions, 3);
	EXPECT_EQ(cpu.z, 0);
	EXPECT_EQ(cpu.n, 0);

	END_TEST();

	START_TEST("LDA Zero page - negative");

	reset_cpu(&cpu, &memory);
	memory.data[0xFFFC] = INS_LDA_ZP;
	memory.data[0xFFFD] = 0x42;
	memory.data[0x42]	= 0x42;
	number_of_instructions = execute_instruction(&cpu, &memory);

	EXPECT_EQ(cpu.a, 0x42);
	EXPECT_EQ(number_of_instructions, 3);
	EXPECT_EQ(cpu.z, 0);
	EXPECT_EQ(cpu.n, 1);

	END_TEST();

	START_TEST("LDA Zero page - zero");

	reset_cpu(&cpu, &memory);
	memory.data[0xFFFC] = INS_LDA_ZP;
	memory.data[0xFFFD] = 0x42;
	memory.data[0x42]	= 0x0;
	number_of_instructions = execute_instruction(&cpu, &memory);

	EXPECT_EQ(cpu.a, 0x0);
	EXPECT_EQ(number_of_instructions, 3);
	EXPECT_EQ(cpu.z, 1);
	EXPECT_EQ(cpu.n, 0);

	END_TEST();
}

void test_lda_zpx(CPU cpu, MEMORY memory)
{
	int number_of_instructions;

	START_TEST("LDA  Zero page X");

	reset_cpu(&cpu, &memory);
	cpu.x = 0x7;
	memory.data[0xFFFC] = INS_LDA_ZPX;
	memory.data[0xFFFD] = 0x42;
	memory.data[0x49] = 0x13;
	number_of_instructions = execute_instruction(&cpu, &memory);

	EXPECT_EQ(cpu.a, 0x13);
	EXPECT_EQ(number_of_instructions, 4);
	EXPECT_EQ(cpu.z, 0);
	EXPECT_EQ(cpu.n, 0);

	END_TEST();

	START_TEST("LDA  Zero page X - negative");

	reset_cpu(&cpu, &memory);
	cpu.x = 0x7;
	memory.data[0xFFFC] = INS_LDA_ZPX;
	memory.data[0xFFFD] = 0x42;
	memory.data[0x49] = 0x42;
	number_of_instructions = execute_instruction(&cpu, &memory);

	EXPECT_EQ(cpu.a, 0x42);
	EXPECT_EQ(number_of_instructions, 4);
	EXPECT_EQ(cpu.z, 0);
	EXPECT_EQ(cpu.n, 1);

	END_TEST();

	START_TEST("LDA  Zero page X - zero");

	reset_cpu(&cpu, &memory);
	cpu.x = 0x7;
	memory.data[0xFFFC] = INS_LDA_ZPX;
	memory.data[0xFFFD] = 0x42;
	memory.data[0x49] = 0x0;
	number_of_instructions = execute_instruction(&cpu, &memory);

	EXPECT_EQ(cpu.a, 0x0);
	EXPECT_EQ(number_of_instructions, 4);
	EXPECT_EQ(cpu.z, 1);
	EXPECT_EQ(cpu.n, 0);

	END_TEST();
}

void test_lda_abs(CPU cpu, MEMORY memory)
{
	int number_of_instructions;

	START_TEST("LDA Absolute");

	reset_cpu(&cpu, &memory);
	memory.data[0xFFFC] = INS_LDA_ABS;
	memory.data[0xFFFD] = 0x42;
	memory.data[0xFFFE] = 0x12;
	memory.data[0x1242] = 0x15;
	number_of_instructions = execute_instruction(&cpu, &memory);

	EXPECT_EQ(cpu.a, 0x15);
	EXPECT_EQ(number_of_instructions, 4);
	EXPECT_EQ(cpu.z, 0);
	EXPECT_EQ(cpu.n, 0);

	END_TEST();

	START_TEST("LDA Absolute - negative");

	reset_cpu(&cpu, &memory);
	memory.data[0xFFFC] = INS_LDA_ABS;
	memory.data[0xFFFD] = 0x42;
	memory.data[0xFFFE] = 0x12;
	memory.data[0x1242] = 0x42;
	number_of_instructions = execute_instruction(&cpu, &memory);

	EXPECT_EQ(cpu.a, 0x42);
	EXPECT_EQ(number_of_instructions, 4);
	EXPECT_EQ(cpu.z, 0);
	EXPECT_EQ(cpu.n, 1);

	END_TEST();

	START_TEST("LDA Absolute - zero");

	reset_cpu(&cpu, &memory);
	memory.data[0xFFFC] = INS_LDA_ABS;
	memory.data[0xFFFD] = 0x42;
	memory.data[0xFFFE] = 0x12;
	memory.data[0x1242] = 0x0;
	number_of_instructions = execute_instruction(&cpu, &memory);

	EXPECT_EQ(cpu.a, 0x0);
	EXPECT_EQ(number_of_instructions, 4);
	EXPECT_EQ(cpu.z, 1);
	EXPECT_EQ(cpu.n, 0);

	END_TEST();
}

void test_lda_absx(CPU cpu, MEMORY memory)
{
	int number_of_instructions;

	START_TEST("LDA Absolute X");

	reset_cpu(&cpu, &memory);
	cpu.x = 0x3;
	memory.data[0xFFFC] = INS_LDA_ABSX;
	memory.data[0xFFFD] = 0x12;
	memory.data[0xFFFE] = 0x0;
	memory.data[0x15] = 0x15;
	number_of_instructions = execute_instruction(&cpu, &memory);

	EXPECT_EQ(cpu.a, 0x15);
	EXPECT_EQ(number_of_instructions, 4);
	EXPECT_EQ(cpu.z, 0);
	EXPECT_EQ(cpu.n, 0);

	END_TEST();

	START_TEST("LDA Absolute X - negative");

	reset_cpu(&cpu, &memory);
	cpu.x = 0x3;
	memory.data[0xFFFC] = INS_LDA_ABSX;
	memory.data[0xFFFD] = 0x12;
	memory.data[0xFFFE] = 0x0;
	memory.data[0x15] = 0x42;
	number_of_instructions = execute_instruction(&cpu, &memory);

	EXPECT_EQ(cpu.a, 0x42);
	EXPECT_EQ(number_of_instructions, 4);
	EXPECT_EQ(cpu.z, 0);
	EXPECT_EQ(cpu.n, 1);

	END_TEST();

	START_TEST("LDA Absolute X - zero");

	reset_cpu(&cpu, &memory);
	cpu.x = 0x3;
	memory.data[0xFFFC] = INS_LDA_ABSX;
	memory.data[0xFFFD] = 0x12;
	memory.data[0xFFFE] = 0x0;
	memory.data[0x15] = 0x0;
	number_of_instructions = execute_instruction(&cpu, &memory);

	EXPECT_EQ(cpu.a, 0x0);
	EXPECT_EQ(number_of_instructions, 4);
	EXPECT_EQ(cpu.z, 1);
	EXPECT_EQ(cpu.n, 0);

	END_TEST();

	START_TEST("LDA Absolute X page crossed");

	reset_cpu(&cpu, &memory);
	cpu.x = 0xF;
	memory.data[0xFFFC] = INS_LDA_ABSX;
	memory.data[0xFFFD] = 0xFF;
	memory.data[0xFFFE] = 0x0;
	memory.data[0x010E] = 0x15;
	number_of_instructions = execute_instruction(&cpu, &memory);

	EXPECT_EQ(cpu.a, 0x15);
	EXPECT_EQ(number_of_instructions, 5);
	EXPECT_EQ(cpu.z, 0);
	EXPECT_EQ(cpu.n, 0);

	END_TEST();

	START_TEST("LDA Absolute X page crossed - negative");

	reset_cpu(&cpu, &memory);
	cpu.x = 0xF;
	memory.data[0xFFFC] = INS_LDA_ABSX;
	memory.data[0xFFFD] = 0xFF;
	memory.data[0xFFFE] = 0x0;
	memory.data[0x010E] = 0x42;
	number_of_instructions = execute_instruction(&cpu, &memory);

	EXPECT_EQ(cpu.a, 0x42);
	EXPECT_EQ(number_of_instructions, 5);
	EXPECT_EQ(cpu.z, 0);
	EXPECT_EQ(cpu.n, 1);

	END_TEST();

	START_TEST("LDA Absolute X page crossed- zero");

	reset_cpu(&cpu, &memory);
	cpu.x = 0xF;
	memory.data[0xFFFC] = INS_LDA_ABSX;
	memory.data[0xFFFD] = 0xFF;
	memory.data[0xFFFE] = 0x0;
	memory.data[0x010E] = 0x0;
	number_of_instructions = execute_instruction(&cpu, &memory);

	EXPECT_EQ(cpu.a, 0x0);
	EXPECT_EQ(number_of_instructions, 5);
	EXPECT_EQ(cpu.z, 1);
	EXPECT_EQ(cpu.n, 0);

	END_TEST();
}
