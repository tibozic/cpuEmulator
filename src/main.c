#include "includes/mytests.h"
#include "cpu.h"

void test_lda_im(CPU cpu, MEMORY memory);
void test_lda_zp(CPU cpu, MEMORY memory);
void test_lda_zpx(CPU cpu, MEMORY memory);
void test_lda_abs(CPU cpu, MEMORY memory);
void test_lda_absx(CPU cpu, MEMORY memory);
void test_lda_indx(CPU cpu, MEMORY memory);
void test_lda_indy(CPU cpu, MEMORY memory);
void test_lda_absy(CPU cpu, MEMORY memory);

void test_ldx_im(CPU cpu, MEMORY memory);
void test_ldx_zp(CPU cpu, MEMORY memory);
void test_ldx_zpy(CPU cpu, MEMORY memory);
void test_ldx_abs(CPU cpu, MEMORY memory);
void test_ldx_absy(CPU cpu, MEMORY memory);

void test_ldy_im(CPU cpu, MEMORY memory);
void test_ldy_zp(CPU cpu, MEMORY memory);
void test_ldy_zpx(CPU cpu, MEMORY memory);
void test_ldy_abs(CPU cpu, MEMORY memory);
void test_ldy_absx(CPU cpu, MEMORY memory);

void test_sta_zp(CPU cpu, MEMORY memory);
void test_sta_zpx(CPU cpu, MEMORY memory);
void test_sta_abs(CPU cpu, MEMORY memory);
void test_sta_absx(CPU cpu, MEMORY memory);
void test_sta_absy(CPU cpu, MEMORY memory);
void test_sta_indx(CPU cpu, MEMORY memory);
void test_sta_indy(CPU cpu, MEMORY memory);

int main(void)
{
	CPU cpu;
	MEMORY memory;

	test_lda_im(cpu, memory);
	test_lda_zp(cpu, memory);
	test_lda_zpx(cpu, memory);
	test_lda_abs(cpu, memory);
	test_lda_absx(cpu, memory);
	test_lda_absy(cpu, memory);
	test_lda_indx(cpu, memory);
	test_lda_indy(cpu, memory);

	test_ldx_im(cpu, memory);
	test_ldx_zp(cpu, memory);
	test_ldx_zpy(cpu, memory);
	test_ldx_abs(cpu, memory);
	test_ldx_absy(cpu, memory);

	test_ldy_im(cpu, memory);
	test_ldy_zp(cpu, memory);
	test_ldy_zpx(cpu, memory);
	test_ldy_abs(cpu, memory);
	test_ldy_absx(cpu, memory);

	test_sta_zp(cpu, memory);
	test_sta_zpx(cpu, memory);
	test_sta_abs(cpu, memory);
	test_sta_absx(cpu, memory);
	test_sta_absy(cpu, memory);
	test_sta_indx(cpu, memory);
	test_sta_indy(cpu, memory);

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

void test_lda_absy(CPU cpu, MEMORY memory)
{
	int number_of_instructions;

	START_TEST("LDA Absolute Y");

	reset_cpu(&cpu, &memory);
	cpu.y = 0x3;
	memory.data[0xFFFC] = INS_LDA_ABSY;
	memory.data[0xFFFD] = 0x12;
	memory.data[0xFFFE] = 0x0;
	memory.data[0x15] = 0x15;
	number_of_instructions = execute_instruction(&cpu, &memory);

	EXPECT_EQ(cpu.a, 0x15);
	EXPECT_EQ(number_of_instructions, 4);
	EXPECT_EQ(cpu.z, 0);
	EXPECT_EQ(cpu.n, 0);

	END_TEST();

	START_TEST("LDA Absolute Y - negative");

	reset_cpu(&cpu, &memory);
	cpu.y = 0x3;
	memory.data[0xFFFC] = INS_LDA_ABSY;
	memory.data[0xFFFD] = 0x12;
	memory.data[0xFFFE] = 0x0;
	memory.data[0x15] = 0x42;
	number_of_instructions = execute_instruction(&cpu, &memory);

	EXPECT_EQ(cpu.a, 0x42);
	EXPECT_EQ(number_of_instructions, 4);
	EXPECT_EQ(cpu.z, 0);
	EXPECT_EQ(cpu.n, 1);

	END_TEST();

	START_TEST("LDA Absolute Y - zero");

	reset_cpu(&cpu, &memory);
	cpu.y = 0x3;
	memory.data[0xFFFC] = INS_LDA_ABSY;
	memory.data[0xFFFD] = 0x12;
	memory.data[0xFFFE] = 0x0;
	memory.data[0x15] = 0x0;
	number_of_instructions = execute_instruction(&cpu, &memory);

	EXPECT_EQ(cpu.a, 0x0);
	EXPECT_EQ(number_of_instructions, 4);
	EXPECT_EQ(cpu.z, 1);
	EXPECT_EQ(cpu.n, 0);

	END_TEST();

	START_TEST("LDA Absolute Y page crossed");

	reset_cpu(&cpu, &memory);
	cpu.y = 0xF;
	memory.data[0xFFFC] = INS_LDA_ABSY;
	memory.data[0xFFFD] = 0xFF;
	memory.data[0xFFFE] = 0x0;
	memory.data[0x010E] = 0x15;
	number_of_instructions = execute_instruction(&cpu, &memory);

	EXPECT_EQ(cpu.a, 0x15);
	EXPECT_EQ(number_of_instructions, 5);
	EXPECT_EQ(cpu.z, 0);
	EXPECT_EQ(cpu.n, 0);

	END_TEST();

	START_TEST("LDA Absolute Y page crossed - negative");

	reset_cpu(&cpu, &memory);
	cpu.x = 0xF;
	memory.data[0xFFFC] = INS_LDA_ABSY;
	memory.data[0xFFFD] = 0xFF;
	memory.data[0xFFFE] = 0x0;
	memory.data[0x010E] = 0x42;
	number_of_instructions = execute_instruction(&cpu, &memory);

	EXPECT_EQ(cpu.a, 0x42);
	EXPECT_EQ(number_of_instructions, 5);
	EXPECT_EQ(cpu.z, 0);
	EXPECT_EQ(cpu.n, 1);

	END_TEST();

	START_TEST("LDA Absolute Y page crossed- zero");

	reset_cpu(&cpu, &memory);
	cpu.x = 0xF;
	memory.data[0xFFFC] = INS_LDA_ABSY;
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

void test_lda_indx(CPU cpu, MEMORY memory)
{
	int number_of_instructions;

	START_TEST("LDA Indirect X");

	reset_cpu(&cpu, &memory);
	cpu.x = 0x04;
	memory.data[0xFFFC] = INS_LDA_INDX;
	memory.data[0xFFFD] = 0x02;
	memory.data[0x0006] = 0x00;
	memory.data[0x0007] = 0x80;
	memory.data[0x8000] = 0x15;
	number_of_instructions = execute_instruction(&cpu, &memory);

	EXPECT_EQ(cpu.a, 0x15);
	EXPECT_EQ(number_of_instructions, 6);
	EXPECT_EQ(cpu.z, 0);
	EXPECT_EQ(cpu.n, 0);

	END_TEST();

	START_TEST("LDA Indirect X - negative");

	reset_cpu(&cpu, &memory);
	cpu.x = 0x04;
	memory.data[0xFFFC] = INS_LDA_INDX;
	memory.data[0xFFFD] = 0x02;
	memory.data[0x0006] = 0x00;
	memory.data[0x0007] = 0x80;
	memory.data[0x8000] = 0x42;
	number_of_instructions = execute_instruction(&cpu, &memory);

	EXPECT_EQ(cpu.a, 0x42);
	EXPECT_EQ(number_of_instructions, 6);
	EXPECT_EQ(cpu.z, 0);
	EXPECT_EQ(cpu.n, 1);

	END_TEST();

	START_TEST("LDA Indirect X - zero");

	reset_cpu(&cpu, &memory);
	cpu.x = 0x04;
	memory.data[0xFFFC] = INS_LDA_INDX;
	memory.data[0xFFFD] = 0x02;
	memory.data[0x0006] = 0x00;
	memory.data[0x0007] = 0x80;
	memory.data[0x8000] = 0x00;
	number_of_instructions = execute_instruction(&cpu, &memory);

	EXPECT_EQ(cpu.a, 0x00);
	EXPECT_EQ(number_of_instructions, 6);
	EXPECT_EQ(cpu.z, 1);
	EXPECT_EQ(cpu.n, 0);

	END_TEST();

}

void test_lda_indy(CPU cpu, MEMORY memory)
{
	int number_of_instructions;

	START_TEST("LDA Indirect Y");

	reset_cpu(&cpu, &memory);
	cpu.y = 0x04;
	memory.data[0xFFFC] = INS_LDA_INDY;
	memory.data[0xFFFD] = 0x02;
	memory.data[0x0002] = 0x00;
	memory.data[0x0003] = 0x80;
	memory.data[0x8004] = 0x15;
	number_of_instructions = execute_instruction(&cpu, &memory);

	EXPECT_EQ(cpu.a, 0x15);
	EXPECT_EQ(number_of_instructions, 5);
	EXPECT_EQ(cpu.z, 0);
	EXPECT_EQ(cpu.n, 0);

	END_TEST();

	START_TEST("LDA Indirect Y - negative");

	reset_cpu(&cpu, &memory);
	cpu.y = 0x04;
	memory.data[0xFFFC] = INS_LDA_INDY;
	memory.data[0xFFFD] = 0x02;
	memory.data[0x0002] = 0x00;
	memory.data[0x0003] = 0x80;
	memory.data[0x8004] = 0x42;
	number_of_instructions = execute_instruction(&cpu, &memory);

	EXPECT_EQ(cpu.a, 0x42);
	EXPECT_EQ(number_of_instructions, 5);
	EXPECT_EQ(cpu.z, 0);
	EXPECT_EQ(cpu.n, 1);

	END_TEST();

	START_TEST("LDA Indirect Y - zero");

	reset_cpu(&cpu, &memory);
	cpu.y = 0x04;
	memory.data[0xFFFC] = INS_LDA_INDY;
	memory.data[0xFFFD] = 0x02;
	memory.data[0x0002] = 0x00;
	memory.data[0x0003] = 0x80;
	memory.data[0x8004] = 0x00;
	number_of_instructions = execute_instruction(&cpu, &memory);

	EXPECT_EQ(cpu.a, 0x00);
	EXPECT_EQ(number_of_instructions, 5);
	EXPECT_EQ(cpu.z, 1);
	EXPECT_EQ(cpu.n, 0);

	END_TEST();

	START_TEST("LDA Indirect Y - page crossed");

	reset_cpu(&cpu, &memory);
	cpu.y = 0x04;
	memory.data[0xFFFC] = INS_LDA_INDY;
	memory.data[0xFFFD] = 0x02;
	memory.data[0x0002] = 0xFF;
	memory.data[0x0003] = 0x00;
	memory.data[0x0103] = 0x15;
	number_of_instructions = execute_instruction(&cpu, &memory);

	EXPECT_EQ(cpu.a, 0x15);
	EXPECT_EQ(number_of_instructions, 6);
	EXPECT_EQ(cpu.z, 0);
	EXPECT_EQ(cpu.n, 0);

	END_TEST();
}

void test_ldx_im(CPU cpu, MEMORY memory)
{
	int number_of_instructions;

	START_TEST("LDX Immediate");

	reset_cpu(&cpu, &memory);
	memory.data[0xFFFC] = INS_LDX_IM;
	memory.data[0xFFFD] = 0x12;
	number_of_instructions = execute_instruction(&cpu, &memory);

	EXPECT_EQ(cpu.x, 0x12);
	EXPECT_EQ(number_of_instructions, 2);
	EXPECT_EQ(cpu.z, 0);
	EXPECT_EQ(cpu.n, 0);
	END_TEST();

	START_TEST("LDX Immediate - negative");

	reset_cpu(&cpu, &memory);
	memory.data[0xFFFC] = INS_LDX_IM;
	memory.data[0xFFFD] = 0x42;
	number_of_instructions = execute_instruction(&cpu, &memory);

	EXPECT_EQ(cpu.x, 0x42);
	EXPECT_EQ(number_of_instructions, 2);
	EXPECT_EQ(cpu.z, 0);
	EXPECT_EQ(cpu.n, 1);
	END_TEST();

	START_TEST("LDX Immediate - zero");

	reset_cpu(&cpu, &memory);
	memory.data[0xFFFC] = INS_LDX_IM;
	memory.data[0xFFFD] = 0x0;
	number_of_instructions = execute_instruction(&cpu, &memory);

	EXPECT_EQ(cpu.x, 0x0);
	EXPECT_EQ(number_of_instructions, 2);
	EXPECT_EQ(cpu.z, 1);
	EXPECT_EQ(cpu.n, 0);
	END_TEST();
}

void test_ldx_zp(CPU cpu, MEMORY memory)
{
	int number_of_instructions;
	START_TEST("LDX Zero page");

	reset_cpu(&cpu, &memory);
	memory.data[0xFFFC] = INS_LDX_ZP;
	memory.data[0xFFFD] = 0x42;
	memory.data[0x42]	= 0x12;
	number_of_instructions = execute_instruction(&cpu, &memory);

	EXPECT_EQ(cpu.x, 0x12);
	EXPECT_EQ(number_of_instructions, 3);
	EXPECT_EQ(cpu.z, 0);
	EXPECT_EQ(cpu.n, 0);

	END_TEST();

	START_TEST("LDX Zero page - negative");

	reset_cpu(&cpu, &memory);
	memory.data[0xFFFC] = INS_LDX_ZP;
	memory.data[0xFFFD] = 0x42;
	memory.data[0x42]	= 0x42;
	number_of_instructions = execute_instruction(&cpu, &memory);

	EXPECT_EQ(cpu.x, 0x42);
	EXPECT_EQ(number_of_instructions, 3);
	EXPECT_EQ(cpu.z, 0);
	EXPECT_EQ(cpu.n, 1);

	END_TEST();

	START_TEST("LDX Zero page - zero");

	reset_cpu(&cpu, &memory);
	memory.data[0xFFFC] = INS_LDX_ZP;
	memory.data[0xFFFD] = 0x42;
	memory.data[0x42]	= 0x0;
	number_of_instructions = execute_instruction(&cpu, &memory);

	EXPECT_EQ(cpu.x, 0x0);
	EXPECT_EQ(number_of_instructions, 3);
	EXPECT_EQ(cpu.z, 1);
	EXPECT_EQ(cpu.n, 0);

	END_TEST();
}

void test_ldx_zpy(CPU cpu, MEMORY memory)
{
	int number_of_instructions;

	START_TEST("LDX  Zero page Y");

	reset_cpu(&cpu, &memory);
	cpu.y = 0x7;
	memory.data[0xFFFC] = INS_LDX_ZPY;
	memory.data[0xFFFD] = 0x42;
	memory.data[0x49] = 0x13;
	number_of_instructions = execute_instruction(&cpu, &memory);

	EXPECT_EQ(cpu.x, 0x13);
	EXPECT_EQ(number_of_instructions, 4);
	EXPECT_EQ(cpu.z, 0);
	EXPECT_EQ(cpu.n, 0);

	END_TEST();

	START_TEST("LDX  Zero page Y - negative");

	reset_cpu(&cpu, &memory);
	cpu.y = 0x7;
	memory.data[0xFFFC] = INS_LDX_ZPY;
	memory.data[0xFFFD] = 0x42;
	memory.data[0x49] = 0x42;
	number_of_instructions = execute_instruction(&cpu, &memory);

	EXPECT_EQ(cpu.x, 0x42);
	EXPECT_EQ(number_of_instructions, 4);
	EXPECT_EQ(cpu.z, 0);
	EXPECT_EQ(cpu.n, 1);

	END_TEST();

	START_TEST("LDX  Zero page Y - zero");

	reset_cpu(&cpu, &memory);
	cpu.y = 0x7;
	memory.data[0xFFFC] = INS_LDX_ZPY;
	memory.data[0xFFFD] = 0x42;
	memory.data[0x49] = 0x0;
	number_of_instructions = execute_instruction(&cpu, &memory);

	EXPECT_EQ(cpu.x, 0x0);
	EXPECT_EQ(number_of_instructions, 4);
	EXPECT_EQ(cpu.z, 1);
	EXPECT_EQ(cpu.n, 0);

	END_TEST();
}

void test_ldx_abs(CPU cpu, MEMORY memory)
{
	int number_of_instructions;

	START_TEST("LDX Absolute");

	reset_cpu(&cpu, &memory);
	memory.data[0xFFFC] = INS_LDX_ABS;
	memory.data[0xFFFD] = 0x42;
	memory.data[0xFFFE] = 0x12;
	memory.data[0x1242] = 0x15;
	number_of_instructions = execute_instruction(&cpu, &memory);

	EXPECT_EQ(cpu.x, 0x15);
	EXPECT_EQ(number_of_instructions, 4);
	EXPECT_EQ(cpu.z, 0);
	EXPECT_EQ(cpu.n, 0);

	END_TEST();

	START_TEST("LDX Absolute - negative");

	reset_cpu(&cpu, &memory);
	memory.data[0xFFFC] = INS_LDX_ABS;
	memory.data[0xFFFD] = 0x42;
	memory.data[0xFFFE] = 0x12;
	memory.data[0x1242] = 0x42;
	number_of_instructions = execute_instruction(&cpu, &memory);

	EXPECT_EQ(cpu.x, 0x42);
	EXPECT_EQ(number_of_instructions, 4);
	EXPECT_EQ(cpu.z, 0);
	EXPECT_EQ(cpu.n, 1);

	END_TEST();

	START_TEST("LDX Absolute - zero");

	reset_cpu(&cpu, &memory);
	memory.data[0xFFFC] = INS_LDX_ABS;
	memory.data[0xFFFD] = 0x42;
	memory.data[0xFFFE] = 0x12;
	memory.data[0x1242] = 0x0;
	number_of_instructions = execute_instruction(&cpu, &memory);

	EXPECT_EQ(cpu.x, 0x0);
	EXPECT_EQ(number_of_instructions, 4);
	EXPECT_EQ(cpu.z, 1);
	EXPECT_EQ(cpu.n, 0);

	END_TEST();
}

void test_ldx_absy(CPU cpu, MEMORY memory)
{
	int number_of_instructions;

	START_TEST("LDX Absolute Y");

	reset_cpu(&cpu, &memory);
	cpu.y = 0x3;
	memory.data[0xFFFC] = INS_LDX_ABSY;
	memory.data[0xFFFD] = 0x12;
	memory.data[0xFFFE] = 0x0;
	memory.data[0x15] = 0x15;
	number_of_instructions = execute_instruction(&cpu, &memory);

	EXPECT_EQ(cpu.x, 0x15);
	EXPECT_EQ(number_of_instructions, 4);
	EXPECT_EQ(cpu.z, 0);
	EXPECT_EQ(cpu.n, 0);

	END_TEST();

	START_TEST("LDX Absolute Y - negative");

	reset_cpu(&cpu, &memory);
	cpu.y = 0x3;
	memory.data[0xFFFC] = INS_LDX_ABSY;
	memory.data[0xFFFD] = 0x12;
	memory.data[0xFFFE] = 0x0;
	memory.data[0x15] = 0x42;
	number_of_instructions = execute_instruction(&cpu, &memory);

	EXPECT_EQ(cpu.x, 0x42);
	EXPECT_EQ(number_of_instructions, 4);
	EXPECT_EQ(cpu.z, 0);
	EXPECT_EQ(cpu.n, 1);

	END_TEST();

	START_TEST("LDX Absolute Y - zero");

	reset_cpu(&cpu, &memory);
	cpu.y = 0x3;
	memory.data[0xFFFC] = INS_LDX_ABSY;
	memory.data[0xFFFD] = 0x12;
	memory.data[0xFFFE] = 0x0;
	memory.data[0x15] = 0x0;
	number_of_instructions = execute_instruction(&cpu, &memory);

	EXPECT_EQ(cpu.x, 0x0);
	EXPECT_EQ(number_of_instructions, 4);
	EXPECT_EQ(cpu.z, 1);
	EXPECT_EQ(cpu.n, 0);

	END_TEST();

	START_TEST("LDX Absolute Y page crossed");

	reset_cpu(&cpu, &memory);
	cpu.y = 0xF;
	memory.data[0xFFFC] = INS_LDX_ABSY;
	memory.data[0xFFFD] = 0xFF;
	memory.data[0xFFFE] = 0x0;
	memory.data[0x010E] = 0x15;
	number_of_instructions = execute_instruction(&cpu, &memory);

	EXPECT_EQ(cpu.x, 0x15);
	EXPECT_EQ(number_of_instructions, 5);
	EXPECT_EQ(cpu.z, 0);
	EXPECT_EQ(cpu.n, 0);

	END_TEST();

	START_TEST("LDX Absolute Y page crossed - negative");

	reset_cpu(&cpu, &memory);
	cpu.y = 0xF;
	memory.data[0xFFFC] = INS_LDX_ABSY;
	memory.data[0xFFFD] = 0xFF;
	memory.data[0xFFFE] = 0x0;
	memory.data[0x010E] = 0x42;
	number_of_instructions = execute_instruction(&cpu, &memory);

	EXPECT_EQ(cpu.x, 0x42);
	EXPECT_EQ(number_of_instructions, 5);
	EXPECT_EQ(cpu.z, 0);
	EXPECT_EQ(cpu.n, 1);

	END_TEST();

	START_TEST("LDX Absolute Y page crossed - zero");

	reset_cpu(&cpu, &memory);
	cpu.y = 0xF;
	memory.data[0xFFFC] = INS_LDX_ABSY;
	memory.data[0xFFFD] = 0xFF;
	memory.data[0xFFFE] = 0x0;
	memory.data[0x010E] = 0x0;
	number_of_instructions = execute_instruction(&cpu, &memory);

	EXPECT_EQ(cpu.x, 0x0);
	EXPECT_EQ(number_of_instructions, 5);
	EXPECT_EQ(cpu.z, 1);
	EXPECT_EQ(cpu.n, 0);

	END_TEST();
}

void test_ldy_im(CPU cpu, MEMORY memory)
{
	int number_of_instructions;

	START_TEST("LDY Immediate");

	reset_cpu(&cpu, &memory);
	memory.data[0xFFFC] = INS_LDY_IM;
	memory.data[0xFFFD] = 0x12;
	number_of_instructions = execute_instruction(&cpu, &memory);

	EXPECT_EQ(cpu.y, 0x12);
	EXPECT_EQ(number_of_instructions, 2);
	EXPECT_EQ(cpu.z, 0);
	EXPECT_EQ(cpu.n, 0);
	END_TEST();

	START_TEST("LDY Immediate - negative");

	reset_cpu(&cpu, &memory);
	memory.data[0xFFFC] = INS_LDY_IM;
	memory.data[0xFFFD] = 0x42;
	number_of_instructions = execute_instruction(&cpu, &memory);

	EXPECT_EQ(cpu.y, 0x42);
	EXPECT_EQ(number_of_instructions, 2);
	EXPECT_EQ(cpu.z, 0);
	EXPECT_EQ(cpu.n, 1);
	END_TEST();

	START_TEST("LDY Immediate - zero");

	reset_cpu(&cpu, &memory);
	memory.data[0xFFFC] = INS_LDY_IM;
	memory.data[0xFFFD] = 0x0;
	number_of_instructions = execute_instruction(&cpu, &memory);

	EXPECT_EQ(cpu.y, 0x0);
	EXPECT_EQ(number_of_instructions, 2);
	EXPECT_EQ(cpu.z, 1);
	EXPECT_EQ(cpu.n, 0);
	END_TEST();
}

void test_ldy_zp(CPU cpu, MEMORY memory)
{
	int number_of_instructions;
	START_TEST("LDY Zero page");

	reset_cpu(&cpu, &memory);
	memory.data[0xFFFC] = INS_LDY_ZP;
	memory.data[0xFFFD] = 0x42;
	memory.data[0x42]	= 0x12;
	number_of_instructions = execute_instruction(&cpu, &memory);

	EXPECT_EQ(cpu.y, 0x12);
	EXPECT_EQ(number_of_instructions, 3);
	EXPECT_EQ(cpu.z, 0);
	EXPECT_EQ(cpu.n, 0);

	END_TEST();

	START_TEST("LDY Zero page - negative");

	reset_cpu(&cpu, &memory);
	memory.data[0xFFFC] = INS_LDY_ZP;
	memory.data[0xFFFD] = 0x42;
	memory.data[0x42]	= 0x42;
	number_of_instructions = execute_instruction(&cpu, &memory);

	EXPECT_EQ(cpu.y, 0x42);
	EXPECT_EQ(number_of_instructions, 3);
	EXPECT_EQ(cpu.z, 0);
	EXPECT_EQ(cpu.n, 1);

	END_TEST();

	START_TEST("LDY Zero page - zero");

	reset_cpu(&cpu, &memory);
	memory.data[0xFFFC] = INS_LDY_ZP;
	memory.data[0xFFFD] = 0x42;
	memory.data[0x42]	= 0x0;
	number_of_instructions = execute_instruction(&cpu, &memory);

	EXPECT_EQ(cpu.y, 0x0);
	EXPECT_EQ(number_of_instructions, 3);
	EXPECT_EQ(cpu.z, 1);
	EXPECT_EQ(cpu.n, 0);

	END_TEST();
}

void test_ldy_zpx(CPU cpu, MEMORY memory)
{
	int number_of_instructions;

	START_TEST("LDY  Zero page X");

	reset_cpu(&cpu, &memory);
	cpu.x = 0x7;
	memory.data[0xFFFC] = INS_LDY_ZPX;
	memory.data[0xFFFD] = 0x42;
	memory.data[0x49] = 0x13;
	number_of_instructions = execute_instruction(&cpu, &memory);

	EXPECT_EQ(cpu.y, 0x13);
	EXPECT_EQ(number_of_instructions, 4);
	EXPECT_EQ(cpu.z, 0);
	EXPECT_EQ(cpu.n, 0);

	END_TEST();

	START_TEST("LDY  Zero page X - negative");

	reset_cpu(&cpu, &memory);
	cpu.x = 0x7;
	memory.data[0xFFFC] = INS_LDY_ZPX;
	memory.data[0xFFFD] = 0x42;
	memory.data[0x49] = 0x42;
	number_of_instructions = execute_instruction(&cpu, &memory);

	EXPECT_EQ(cpu.y, 0x42);
	EXPECT_EQ(number_of_instructions, 4);
	EXPECT_EQ(cpu.z, 0);
	EXPECT_EQ(cpu.n, 1);

	END_TEST();

	START_TEST("LDY  Zero page X - zero");

	reset_cpu(&cpu, &memory);
	cpu.x = 0x7;
	memory.data[0xFFFC] = INS_LDY_ZPX;
	memory.data[0xFFFD] = 0x42;
	memory.data[0x49] = 0x0;
	number_of_instructions = execute_instruction(&cpu, &memory);

	EXPECT_EQ(cpu.y, 0x0);
	EXPECT_EQ(number_of_instructions, 4);
	EXPECT_EQ(cpu.z, 1);
	EXPECT_EQ(cpu.n, 0);

	END_TEST();
}

void test_ldy_abs(CPU cpu, MEMORY memory)
{
	int number_of_instructions;

	START_TEST("LDY Absolute");

	reset_cpu(&cpu, &memory);
	memory.data[0xFFFC] = INS_LDY_ABS;
	memory.data[0xFFFD] = 0x42;
	memory.data[0xFFFE] = 0x12;
	memory.data[0x1242] = 0x15;
	number_of_instructions = execute_instruction(&cpu, &memory);

	EXPECT_EQ(cpu.y, 0x15);
	EXPECT_EQ(number_of_instructions, 4);
	EXPECT_EQ(cpu.z, 0);
	EXPECT_EQ(cpu.n, 0);

	END_TEST();

	START_TEST("LDY Absolute - negative");

	reset_cpu(&cpu, &memory);
	memory.data[0xFFFC] = INS_LDY_ABS;
	memory.data[0xFFFD] = 0x42;
	memory.data[0xFFFE] = 0x12;
	memory.data[0x1242] = 0x42;
	number_of_instructions = execute_instruction(&cpu, &memory);

	EXPECT_EQ(cpu.y, 0x42);
	EXPECT_EQ(number_of_instructions, 4);
	EXPECT_EQ(cpu.z, 0);
	EXPECT_EQ(cpu.n, 1);

	END_TEST();

	START_TEST("LDY Absolute - zero");

	reset_cpu(&cpu, &memory);
	memory.data[0xFFFC] = INS_LDY_ABS;
	memory.data[0xFFFD] = 0x42;
	memory.data[0xFFFE] = 0x12;
	memory.data[0x1242] = 0x0;
	number_of_instructions = execute_instruction(&cpu, &memory);

	EXPECT_EQ(cpu.y, 0x0);
	EXPECT_EQ(number_of_instructions, 4);
	EXPECT_EQ(cpu.z, 1);
	EXPECT_EQ(cpu.n, 0);

	END_TEST();
}

void test_ldy_absx(CPU cpu, MEMORY memory)
{
	int number_of_instructions;

	START_TEST("LDY Absolute X");

	reset_cpu(&cpu, &memory);
	cpu.x = 0x3;
	memory.data[0xFFFC] = INS_LDY_ABSX;
	memory.data[0xFFFD] = 0x12;
	memory.data[0xFFFE] = 0x0;
	memory.data[0x15] = 0x15;
	number_of_instructions = execute_instruction(&cpu, &memory);

	EXPECT_EQ(cpu.y, 0x15);
	EXPECT_EQ(number_of_instructions, 4);
	EXPECT_EQ(cpu.z, 0);
	EXPECT_EQ(cpu.n, 0);

	END_TEST();

	START_TEST("LDY Absolute X - negative");

	reset_cpu(&cpu, &memory);
	cpu.x = 0x3;
	memory.data[0xFFFC] = INS_LDY_ABSX;
	memory.data[0xFFFD] = 0x12;
	memory.data[0xFFFE] = 0x0;
	memory.data[0x15] = 0x42;
	number_of_instructions = execute_instruction(&cpu, &memory);

	EXPECT_EQ(cpu.y, 0x42);
	EXPECT_EQ(number_of_instructions, 4);
	EXPECT_EQ(cpu.z, 0);
	EXPECT_EQ(cpu.n, 1);

	END_TEST();

	START_TEST("LDY Absolute X - zero");

	reset_cpu(&cpu, &memory);
	cpu.x = 0x3;
	memory.data[0xFFFC] = INS_LDY_ABSX;
	memory.data[0xFFFD] = 0x12;
	memory.data[0xFFFE] = 0x0;
	memory.data[0x15] = 0x0;
	number_of_instructions = execute_instruction(&cpu, &memory);

	EXPECT_EQ(cpu.y, 0x0);
	EXPECT_EQ(number_of_instructions, 4);
	EXPECT_EQ(cpu.z, 1);
	EXPECT_EQ(cpu.n, 0);

	END_TEST();

	START_TEST("LDY Absolute X page crossed");

	reset_cpu(&cpu, &memory);
	cpu.x = 0xF;
	memory.data[0xFFFC] = INS_LDY_ABSX;
	memory.data[0xFFFD] = 0xFF;
	memory.data[0xFFFE] = 0x0;
	memory.data[0x010E] = 0x15;
	number_of_instructions = execute_instruction(&cpu, &memory);

	EXPECT_EQ(cpu.y, 0x15);
	EXPECT_EQ(number_of_instructions, 5);
	EXPECT_EQ(cpu.z, 0);
	EXPECT_EQ(cpu.n, 0);

	END_TEST();

	START_TEST("LDY Absolute X page crossed - negative");

	reset_cpu(&cpu, &memory);
	cpu.x = 0xF;
	memory.data[0xFFFC] = INS_LDY_ABSX;
	memory.data[0xFFFD] = 0xFF;
	memory.data[0xFFFE] = 0x0;
	memory.data[0x010E] = 0x42;
	number_of_instructions = execute_instruction(&cpu, &memory);

	EXPECT_EQ(cpu.y, 0x42);
	EXPECT_EQ(number_of_instructions, 5);
	EXPECT_EQ(cpu.z, 0);
	EXPECT_EQ(cpu.n, 1);

	END_TEST();

	START_TEST("LDY Absolute X page crossed - zero");

	reset_cpu(&cpu, &memory);
	cpu.x = 0xF;
	memory.data[0xFFFC] = INS_LDY_ABSX;
	memory.data[0xFFFD] = 0xFF;
	memory.data[0xFFFE] = 0x0;
	memory.data[0x010E] = 0x0;
	number_of_instructions = execute_instruction(&cpu, &memory);

	EXPECT_EQ(cpu.y, 0x0);
	EXPECT_EQ(number_of_instructions, 5);
	EXPECT_EQ(cpu.z, 1);
	EXPECT_EQ(cpu.n, 0);

	END_TEST();
}

void test_sta_zp(CPU cpu, MEMORY memory)
{
	int number_of_instructions;

	START_TEST("STA zero page");

	reset_cpu(&cpu, &memory);
	cpu.a = 0x12;
	memory.data[0xFFFC] = INS_STA_ZP;
	memory.data[0xFFFD] = 0x0033;

	number_of_instructions = execute_instruction(&cpu, &memory);

	EXPECT_EQ(cpu.a, memory.data[0x0033]);
	EXPECT_EQ(number_of_instructions, 3);

	END_TEST();
}

void test_sta_zpx(CPU cpu, MEMORY memory)
{
	int number_of_instructions;

	START_TEST("STA zero page X");

	reset_cpu(&cpu, &memory);
	cpu.a = 0x12;
	cpu.x = 0x13;
	memory.data[0xFFFC] = INS_STA_ZPX;
	memory.data[0xFFFD] = 0x0033;

	number_of_instructions = execute_instruction(&cpu, &memory);

	EXPECT_EQ(cpu.a, memory.data[0x33 + 0x13]);
	EXPECT_EQ(number_of_instructions, 4);

	END_TEST();

	START_TEST("STA zero page X - page crossed");

	reset_cpu(&cpu, &memory);
	cpu.a = 0x12;
	cpu.x = 0xFF;
	memory.data[0xFFFC] = INS_STA_ZPX;
	memory.data[0xFFFD] = 0x0033;

	number_of_instructions = execute_instruction(&cpu, &memory);

	EXPECT_EQ(cpu.a, memory.data[0x32]);
	EXPECT_EQ(number_of_instructions, 4);

	END_TEST();
}

void test_sta_abs(CPU cpu, MEMORY memory)
{
	int number_of_instructions;

	START_TEST("STA absolute");

	reset_cpu(&cpu, &memory);

	cpu.a = 0x12;
	memory.data[0xFFFC] = INS_STA_ABS;
	memory.data[0xFFFD] = 0x34;
	memory.data[0xFFFE] = 0x12;

	number_of_instructions = execute_instruction(&cpu, &memory);

	EXPECT_EQ(cpu.a, memory.data[0x1234]);
	EXPECT_EQ(number_of_instructions, 4);

	END_TEST();

}

void test_sta_absx(CPU cpu, MEMORY memory)
{
	int number_of_instructions;

	START_TEST("STA absolute X");

	reset_cpu(&cpu, &memory);

	cpu.x = 0x03;
	cpu.a = 0x12;
	memory.data[0xFFFC] = INS_STA_ABSX;
	memory.data[0xFFFD] = 0x34;
	memory.data[0xFFFE] = 0x12;

	number_of_instructions = execute_instruction(&cpu, &memory);

	EXPECT_EQ(cpu.a, memory.data[0x1234 + cpu.x]);
	EXPECT_EQ(number_of_instructions, 5);

	END_TEST();
}

void test_sta_absy(CPU cpu, MEMORY memory)
{
	int number_of_instructions;

	START_TEST("STA absolute Y");

	reset_cpu(&cpu, &memory);

	cpu.y = 0x03;
	cpu.a = 0x12;
	memory.data[0xFFFC] = INS_STA_ABSY;
	memory.data[0xFFFD] = 0x34;
	memory.data[0xFFFE] = 0x12;

	number_of_instructions = execute_instruction(&cpu, &memory);

	EXPECT_EQ(cpu.a, memory.data[0x1234 + cpu.y]);
	EXPECT_EQ(number_of_instructions, 5);

	END_TEST();
}

void test_sta_indx(CPU cpu, MEMORY memory)
{
	int number_of_instructions;

	START_TEST("STA Indirect X");

	reset_cpu(&cpu, &memory);
	cpu.a = 0x12;
	cpu.x = 0x04;
	memory.data[0xFFFC] = INS_STA_INDX;
	memory.data[0xFFFD] = 0x02;
	memory.data[0x0006] = 0x00;
	memory.data[0x0007] = 0x80;

	number_of_instructions = execute_instruction(&cpu, &memory);

	EXPECT_EQ(cpu.a, memory.data[0x8000]);
	EXPECT_EQ(number_of_instructions, 6);

	END_TEST();
}

void test_sta_indy(CPU cpu, MEMORY memory)
{
	int number_of_instructions;

	START_TEST("STA Indirect X");

	reset_cpu(&cpu, &memory);
	cpu.a = 0x12;
	cpu.y = 0x04;
	memory.data[0xFFFC] = INS_STA_INDY;
	memory.data[0xFFFD] = 0x02;
	memory.data[0x0002] = 0x00;
	memory.data[0x0003] = 0x80;

	number_of_instructions = execute_instruction(&cpu, &memory);

	EXPECT_EQ(cpu.a, memory.data[0x8000 + cpu.y]);
	EXPECT_EQ(number_of_instructions, 6);

	END_TEST();
}
