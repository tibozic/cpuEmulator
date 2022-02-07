#include "includes/mytests.h"
#include "cpu.h"

/* Tests for LDA */
void test_lda_im(CPU cpu, MEMORY memory);
void test_lda_zp(CPU cpu, MEMORY memory);
void test_lda_zpx(CPU cpu, MEMORY memory);
void test_lda_abs(CPU cpu, MEMORY memory);
void test_lda_absx(CPU cpu, MEMORY memory);
void test_lda_indx(CPU cpu, MEMORY memory);
void test_lda_indy(CPU cpu, MEMORY memory);
void test_lda_absy(CPU cpu, MEMORY memory);

/* Tests for LDX */
void test_ldx_im(CPU cpu, MEMORY memory);
void test_ldx_zp(CPU cpu, MEMORY memory);
void test_ldx_zpy(CPU cpu, MEMORY memory);
void test_ldx_abs(CPU cpu, MEMORY memory);
void test_ldx_absy(CPU cpu, MEMORY memory);

/* Tests for LDY */
void test_ldy_im(CPU cpu, MEMORY memory);
void test_ldy_zp(CPU cpu, MEMORY memory);
void test_ldy_zpx(CPU cpu, MEMORY memory);
void test_ldy_abs(CPU cpu, MEMORY memory);
void test_ldy_absx(CPU cpu, MEMORY memory);

/* Tests for STA */
void test_sta_zp(CPU cpu, MEMORY memory);
void test_sta_zpx(CPU cpu, MEMORY memory);
void test_sta_abs(CPU cpu, MEMORY memory);
void test_sta_absx(CPU cpu, MEMORY memory);
void test_sta_absy(CPU cpu, MEMORY memory);
void test_sta_indx(CPU cpu, MEMORY memory);
void test_sta_indy(CPU cpu, MEMORY memory);

/* Tests for STX */
void test_stx_zp(CPU cpu, MEMORY memory);
void test_stx_zpy(CPU cpu, MEMORY memory);
void test_stx_abs(CPU cpu, MEMORY memory);

/* Tests for STY */
void test_sty_zp(CPU cpu, MEMORY memory);
void test_sty_zpx(CPU cpu, MEMORY memory);
void test_sty_abs(CPU cpu, MEMORY memory);

/* Tests for transfer instructions */
void test_tax(CPU cpu, MEMORY memory);
void test_tay(CPU cpu, MEMORY memory);
void test_txa(CPU cpu, MEMORY memory);
void test_tya(CPU cpu, MEMORY memory);
void test_tsx(CPU cpu, MEMORY memory);

/* Tests for stack instructions */
void test_pha(CPU cpu, MEMORY memory);
void test_pla(CPU cpu, MEMORY memory);

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

	test_stx_zp(cpu, memory);
	test_stx_zpy(cpu, memory);
	test_stx_abs(cpu, memory);

	test_sty_zp(cpu, memory);
	test_sty_zpx(cpu, memory);
	test_sty_abs(cpu, memory);

	test_tax(cpu, memory);

	test_tay(cpu, memory);

	test_txa(cpu, memory);

	test_tya(cpu, memory);

	test_tsx(cpu, memory);

	test_pha(cpu, memory);

	test_pla(cpu, memory);

	report_print();
}

void test_lda_im(CPU cpu, MEMORY memory)
{
	int number_of_instructions;

	TEST_START("LDA Immediate");

	cpu_reset(&cpu, &memory);
	memory.data[0xFFFC] = INS_LDA_IM;
	memory.data[0xFFFD] = 0x12;
	number_of_instructions = instruction_execute(&cpu, &memory);

	EXPECT_EQ(cpu.a, 0x12);
	EXPECT_EQ(number_of_instructions, 2);
	EXPECT_EQ(cpu.z, 0);
	EXPECT_EQ(cpu.n, 0);
	TEST_END();

	TEST_START("LDA Immediate - negative");

	cpu_reset(&cpu, &memory);
	memory.data[0xFFFC] = INS_LDA_IM;
	memory.data[0xFFFD] = 0x42;
	number_of_instructions = instruction_execute(&cpu, &memory);

	EXPECT_EQ(cpu.a, 0x42);
	EXPECT_EQ(number_of_instructions, 2);
	EXPECT_EQ(cpu.z, 0);
	EXPECT_EQ(cpu.n, 1);
	TEST_END();

	TEST_START("LDA Immediate - zero");

	cpu_reset(&cpu, &memory);
	memory.data[0xFFFC] = INS_LDA_IM;
	memory.data[0xFFFD] = 0x0;
	number_of_instructions = instruction_execute(&cpu, &memory);

	EXPECT_EQ(cpu.a, 0x0);
	EXPECT_EQ(number_of_instructions, 2);
	EXPECT_EQ(cpu.z, 1);
	EXPECT_EQ(cpu.n, 0);
	TEST_END();
}

void test_lda_zp(CPU cpu, MEMORY memory)
{
	int number_of_instructions;
	TEST_START("LDA Zero page");

	cpu_reset(&cpu, &memory);
	memory.data[0xFFFC] = INS_LDA_ZP;
	memory.data[0xFFFD] = 0x42;
	memory.data[0x42]	= 0x12;
	number_of_instructions = instruction_execute(&cpu, &memory);

	EXPECT_EQ(cpu.a, 0x12);
	EXPECT_EQ(number_of_instructions, 3);
	EXPECT_EQ(cpu.z, 0);
	EXPECT_EQ(cpu.n, 0);

	TEST_END();

	TEST_START("LDA Zero page - negative");

	cpu_reset(&cpu, &memory);
	memory.data[0xFFFC] = INS_LDA_ZP;
	memory.data[0xFFFD] = 0x42;
	memory.data[0x42]	= 0x42;
	number_of_instructions = instruction_execute(&cpu, &memory);

	EXPECT_EQ(cpu.a, 0x42);
	EXPECT_EQ(number_of_instructions, 3);
	EXPECT_EQ(cpu.z, 0);
	EXPECT_EQ(cpu.n, 1);

	TEST_END();

	TEST_START("LDA Zero page - zero");

	cpu_reset(&cpu, &memory);
	memory.data[0xFFFC] = INS_LDA_ZP;
	memory.data[0xFFFD] = 0x42;
	memory.data[0x42]	= 0x0;
	number_of_instructions = instruction_execute(&cpu, &memory);

	EXPECT_EQ(cpu.a, 0x0);
	EXPECT_EQ(number_of_instructions, 3);
	EXPECT_EQ(cpu.z, 1);
	EXPECT_EQ(cpu.n, 0);

	TEST_END();
}

void test_lda_zpx(CPU cpu, MEMORY memory)
{
	int number_of_instructions;

	TEST_START("LDA  Zero page X");

	cpu_reset(&cpu, &memory);
	cpu.x = 0x7;
	memory.data[0xFFFC] = INS_LDA_ZPX;
	memory.data[0xFFFD] = 0x42;
	memory.data[0x49] = 0x13;
	number_of_instructions = instruction_execute(&cpu, &memory);

	EXPECT_EQ(cpu.a, 0x13);
	EXPECT_EQ(number_of_instructions, 4);
	EXPECT_EQ(cpu.z, 0);
	EXPECT_EQ(cpu.n, 0);

	TEST_END();

	TEST_START("LDA  Zero page X - negative");

	cpu_reset(&cpu, &memory);
	cpu.x = 0x7;
	memory.data[0xFFFC] = INS_LDA_ZPX;
	memory.data[0xFFFD] = 0x42;
	memory.data[0x49] = 0x42;
	number_of_instructions = instruction_execute(&cpu, &memory);

	EXPECT_EQ(cpu.a, 0x42);
	EXPECT_EQ(number_of_instructions, 4);
	EXPECT_EQ(cpu.z, 0);
	EXPECT_EQ(cpu.n, 1);

	TEST_END();

	TEST_START("LDA  Zero page X - zero");

	cpu_reset(&cpu, &memory);
	cpu.x = 0x7;
	memory.data[0xFFFC] = INS_LDA_ZPX;
	memory.data[0xFFFD] = 0x42;
	memory.data[0x49] = 0x0;
	number_of_instructions = instruction_execute(&cpu, &memory);

	EXPECT_EQ(cpu.a, 0x0);
	EXPECT_EQ(number_of_instructions, 4);
	EXPECT_EQ(cpu.z, 1);
	EXPECT_EQ(cpu.n, 0);

	TEST_END();
}

void test_lda_abs(CPU cpu, MEMORY memory)
{
	int number_of_instructions;

	TEST_START("LDA Absolute");

	cpu_reset(&cpu, &memory);
	memory.data[0xFFFC] = INS_LDA_ABS;
	memory.data[0xFFFD] = 0x42;
	memory.data[0xFFFE] = 0x12;
	memory.data[0x1242] = 0x15;
	number_of_instructions = instruction_execute(&cpu, &memory);

	EXPECT_EQ(cpu.a, 0x15);
	EXPECT_EQ(number_of_instructions, 4);
	EXPECT_EQ(cpu.z, 0);
	EXPECT_EQ(cpu.n, 0);

	TEST_END();

	TEST_START("LDA Absolute - negative");

	cpu_reset(&cpu, &memory);
	memory.data[0xFFFC] = INS_LDA_ABS;
	memory.data[0xFFFD] = 0x42;
	memory.data[0xFFFE] = 0x12;
	memory.data[0x1242] = 0x42;
	number_of_instructions = instruction_execute(&cpu, &memory);

	EXPECT_EQ(cpu.a, 0x42);
	EXPECT_EQ(number_of_instructions, 4);
	EXPECT_EQ(cpu.z, 0);
	EXPECT_EQ(cpu.n, 1);

	TEST_END();

	TEST_START("LDA Absolute - zero");

	cpu_reset(&cpu, &memory);
	memory.data[0xFFFC] = INS_LDA_ABS;
	memory.data[0xFFFD] = 0x42;
	memory.data[0xFFFE] = 0x12;
	memory.data[0x1242] = 0x0;
	number_of_instructions = instruction_execute(&cpu, &memory);

	EXPECT_EQ(cpu.a, 0x0);
	EXPECT_EQ(number_of_instructions, 4);
	EXPECT_EQ(cpu.z, 1);
	EXPECT_EQ(cpu.n, 0);

	TEST_END();
}

void test_lda_absx(CPU cpu, MEMORY memory)
{
	int number_of_instructions;

	TEST_START("LDA Absolute X");

	cpu_reset(&cpu, &memory);
	cpu.x = 0x3;
	memory.data[0xFFFC] = INS_LDA_ABSX;
	memory.data[0xFFFD] = 0x12;
	memory.data[0xFFFE] = 0x0;
	memory.data[0x15] = 0x15;
	number_of_instructions = instruction_execute(&cpu, &memory);

	EXPECT_EQ(cpu.a, 0x15);
	EXPECT_EQ(number_of_instructions, 4);
	EXPECT_EQ(cpu.z, 0);
	EXPECT_EQ(cpu.n, 0);

	TEST_END();

	TEST_START("LDA Absolute X - negative");

	cpu_reset(&cpu, &memory);
	cpu.x = 0x3;
	memory.data[0xFFFC] = INS_LDA_ABSX;
	memory.data[0xFFFD] = 0x12;
	memory.data[0xFFFE] = 0x0;
	memory.data[0x15] = 0x42;
	number_of_instructions = instruction_execute(&cpu, &memory);

	EXPECT_EQ(cpu.a, 0x42);
	EXPECT_EQ(number_of_instructions, 4);
	EXPECT_EQ(cpu.z, 0);
	EXPECT_EQ(cpu.n, 1);

	TEST_END();

	TEST_START("LDA Absolute X - zero");

	cpu_reset(&cpu, &memory);
	cpu.x = 0x3;
	memory.data[0xFFFC] = INS_LDA_ABSX;
	memory.data[0xFFFD] = 0x12;
	memory.data[0xFFFE] = 0x0;
	memory.data[0x15] = 0x0;
	number_of_instructions = instruction_execute(&cpu, &memory);

	EXPECT_EQ(cpu.a, 0x0);
	EXPECT_EQ(number_of_instructions, 4);
	EXPECT_EQ(cpu.z, 1);
	EXPECT_EQ(cpu.n, 0);

	TEST_END();

	TEST_START("LDA Absolute X page crossed");

	cpu_reset(&cpu, &memory);
	cpu.x = 0xF;
	memory.data[0xFFFC] = INS_LDA_ABSX;
	memory.data[0xFFFD] = 0xFF;
	memory.data[0xFFFE] = 0x0;
	memory.data[0x010E] = 0x15;
	number_of_instructions = instruction_execute(&cpu, &memory);

	EXPECT_EQ(cpu.a, 0x15);
	EXPECT_EQ(number_of_instructions, 5);
	EXPECT_EQ(cpu.z, 0);
	EXPECT_EQ(cpu.n, 0);

	TEST_END();

	TEST_START("LDA Absolute X page crossed - negative");

	cpu_reset(&cpu, &memory);
	cpu.x = 0xF;
	memory.data[0xFFFC] = INS_LDA_ABSX;
	memory.data[0xFFFD] = 0xFF;
	memory.data[0xFFFE] = 0x0;
	memory.data[0x010E] = 0x42;
	number_of_instructions = instruction_execute(&cpu, &memory);

	EXPECT_EQ(cpu.a, 0x42);
	EXPECT_EQ(number_of_instructions, 5);
	EXPECT_EQ(cpu.z, 0);
	EXPECT_EQ(cpu.n, 1);

	TEST_END();

	TEST_START("LDA Absolute X page crossed- zero");

	cpu_reset(&cpu, &memory);
	cpu.x = 0xF;
	memory.data[0xFFFC] = INS_LDA_ABSX;
	memory.data[0xFFFD] = 0xFF;
	memory.data[0xFFFE] = 0x0;
	memory.data[0x010E] = 0x0;
	number_of_instructions = instruction_execute(&cpu, &memory);

	EXPECT_EQ(cpu.a, 0x0);
	EXPECT_EQ(number_of_instructions, 5);
	EXPECT_EQ(cpu.z, 1);
	EXPECT_EQ(cpu.n, 0);

	TEST_END();
}

void test_lda_absy(CPU cpu, MEMORY memory)
{
	int number_of_instructions;

	TEST_START("LDA Absolute Y");

	cpu_reset(&cpu, &memory);
	cpu.y = 0x3;
	memory.data[0xFFFC] = INS_LDA_ABSY;
	memory.data[0xFFFD] = 0x12;
	memory.data[0xFFFE] = 0x0;
	memory.data[0x15] = 0x15;
	number_of_instructions = instruction_execute(&cpu, &memory);

	EXPECT_EQ(cpu.a, 0x15);
	EXPECT_EQ(number_of_instructions, 4);
	EXPECT_EQ(cpu.z, 0);
	EXPECT_EQ(cpu.n, 0);

	TEST_END();

	TEST_START("LDA Absolute Y - negative");

	cpu_reset(&cpu, &memory);
	cpu.y = 0x3;
	memory.data[0xFFFC] = INS_LDA_ABSY;
	memory.data[0xFFFD] = 0x12;
	memory.data[0xFFFE] = 0x0;
	memory.data[0x15] = 0x42;
	number_of_instructions = instruction_execute(&cpu, &memory);

	EXPECT_EQ(cpu.a, 0x42);
	EXPECT_EQ(number_of_instructions, 4);
	EXPECT_EQ(cpu.z, 0);
	EXPECT_EQ(cpu.n, 1);

	TEST_END();

	TEST_START("LDA Absolute Y - zero");

	cpu_reset(&cpu, &memory);
	cpu.y = 0x3;
	memory.data[0xFFFC] = INS_LDA_ABSY;
	memory.data[0xFFFD] = 0x12;
	memory.data[0xFFFE] = 0x0;
	memory.data[0x15] = 0x0;
	number_of_instructions = instruction_execute(&cpu, &memory);

	EXPECT_EQ(cpu.a, 0x0);
	EXPECT_EQ(number_of_instructions, 4);
	EXPECT_EQ(cpu.z, 1);
	EXPECT_EQ(cpu.n, 0);

	TEST_END();

	TEST_START("LDA Absolute Y page crossed");

	cpu_reset(&cpu, &memory);
	cpu.y = 0xF;
	memory.data[0xFFFC] = INS_LDA_ABSY;
	memory.data[0xFFFD] = 0xFF;
	memory.data[0xFFFE] = 0x0;
	memory.data[0x010E] = 0x15;
	number_of_instructions = instruction_execute(&cpu, &memory);

	EXPECT_EQ(cpu.a, 0x15);
	EXPECT_EQ(number_of_instructions, 5);
	EXPECT_EQ(cpu.z, 0);
	EXPECT_EQ(cpu.n, 0);

	TEST_END();

	TEST_START("LDA Absolute Y page crossed - negative");

	cpu_reset(&cpu, &memory);
	cpu.x = 0xF;
	memory.data[0xFFFC] = INS_LDA_ABSY;
	memory.data[0xFFFD] = 0xFF;
	memory.data[0xFFFE] = 0x0;
	memory.data[0x010E] = 0x42;
	number_of_instructions = instruction_execute(&cpu, &memory);

	EXPECT_EQ(cpu.a, 0x42);
	EXPECT_EQ(number_of_instructions, 5);
	EXPECT_EQ(cpu.z, 0);
	EXPECT_EQ(cpu.n, 1);

	TEST_END();

	TEST_START("LDA Absolute Y page crossed- zero");

	cpu_reset(&cpu, &memory);
	cpu.x = 0xF;
	memory.data[0xFFFC] = INS_LDA_ABSY;
	memory.data[0xFFFD] = 0xFF;
	memory.data[0xFFFE] = 0x0;
	memory.data[0x010E] = 0x0;
	number_of_instructions = instruction_execute(&cpu, &memory);

	EXPECT_EQ(cpu.a, 0x0);
	EXPECT_EQ(number_of_instructions, 5);
	EXPECT_EQ(cpu.z, 1);
	EXPECT_EQ(cpu.n, 0);

	TEST_END();
}

void test_lda_indx(CPU cpu, MEMORY memory)
{
	int number_of_instructions;

	TEST_START("LDA Indirect X");

	cpu_reset(&cpu, &memory);
	cpu.x = 0x04;
	memory.data[0xFFFC] = INS_LDA_INDX;
	memory.data[0xFFFD] = 0x02;
	memory.data[0x0006] = 0x00;
	memory.data[0x0007] = 0x80;
	memory.data[0x8000] = 0x15;
	number_of_instructions = instruction_execute(&cpu, &memory);

	EXPECT_EQ(cpu.a, 0x15);
	EXPECT_EQ(number_of_instructions, 6);
	EXPECT_EQ(cpu.z, 0);
	EXPECT_EQ(cpu.n, 0);

	TEST_END();

	TEST_START("LDA Indirect X - negative");

	cpu_reset(&cpu, &memory);
	cpu.x = 0x04;
	memory.data[0xFFFC] = INS_LDA_INDX;
	memory.data[0xFFFD] = 0x02;
	memory.data[0x0006] = 0x00;
	memory.data[0x0007] = 0x80;
	memory.data[0x8000] = 0x42;
	number_of_instructions = instruction_execute(&cpu, &memory);

	EXPECT_EQ(cpu.a, 0x42);
	EXPECT_EQ(number_of_instructions, 6);
	EXPECT_EQ(cpu.z, 0);
	EXPECT_EQ(cpu.n, 1);

	TEST_END();

	TEST_START("LDA Indirect X - zero");

	cpu_reset(&cpu, &memory);
	cpu.x = 0x04;
	memory.data[0xFFFC] = INS_LDA_INDX;
	memory.data[0xFFFD] = 0x02;
	memory.data[0x0006] = 0x00;
	memory.data[0x0007] = 0x80;
	memory.data[0x8000] = 0x00;
	number_of_instructions = instruction_execute(&cpu, &memory);

	EXPECT_EQ(cpu.a, 0x00);
	EXPECT_EQ(number_of_instructions, 6);
	EXPECT_EQ(cpu.z, 1);
	EXPECT_EQ(cpu.n, 0);

	TEST_END();

}

void test_lda_indy(CPU cpu, MEMORY memory)
{
	int number_of_instructions;

	TEST_START("LDA Indirect Y");

	cpu_reset(&cpu, &memory);
	cpu.y = 0x04;
	memory.data[0xFFFC] = INS_LDA_INDY;
	memory.data[0xFFFD] = 0x02;
	memory.data[0x0002] = 0x00;
	memory.data[0x0003] = 0x80;
	memory.data[0x8004] = 0x15;
	number_of_instructions = instruction_execute(&cpu, &memory);

	EXPECT_EQ(cpu.a, 0x15);
	EXPECT_EQ(number_of_instructions, 5);
	EXPECT_EQ(cpu.z, 0);
	EXPECT_EQ(cpu.n, 0);

	TEST_END();

	TEST_START("LDA Indirect Y - negative");

	cpu_reset(&cpu, &memory);
	cpu.y = 0x04;
	memory.data[0xFFFC] = INS_LDA_INDY;
	memory.data[0xFFFD] = 0x02;
	memory.data[0x0002] = 0x00;
	memory.data[0x0003] = 0x80;
	memory.data[0x8004] = 0x42;
	number_of_instructions = instruction_execute(&cpu, &memory);

	EXPECT_EQ(cpu.a, 0x42);
	EXPECT_EQ(number_of_instructions, 5);
	EXPECT_EQ(cpu.z, 0);
	EXPECT_EQ(cpu.n, 1);

	TEST_END();

	TEST_START("LDA Indirect Y - zero");

	cpu_reset(&cpu, &memory);
	cpu.y = 0x04;
	memory.data[0xFFFC] = INS_LDA_INDY;
	memory.data[0xFFFD] = 0x02;
	memory.data[0x0002] = 0x00;
	memory.data[0x0003] = 0x80;
	memory.data[0x8004] = 0x00;
	number_of_instructions = instruction_execute(&cpu, &memory);

	EXPECT_EQ(cpu.a, 0x00);
	EXPECT_EQ(number_of_instructions, 5);
	EXPECT_EQ(cpu.z, 1);
	EXPECT_EQ(cpu.n, 0);

	TEST_END();

	TEST_START("LDA Indirect Y - page crossed");

	cpu_reset(&cpu, &memory);
	cpu.y = 0x04;
	memory.data[0xFFFC] = INS_LDA_INDY;
	memory.data[0xFFFD] = 0x02;
	memory.data[0x0002] = 0xFF;
	memory.data[0x0003] = 0x00;
	memory.data[0x0103] = 0x15;
	number_of_instructions = instruction_execute(&cpu, &memory);

	EXPECT_EQ(cpu.a, 0x15);
	EXPECT_EQ(number_of_instructions, 6);
	EXPECT_EQ(cpu.z, 0);
	EXPECT_EQ(cpu.n, 0);

	TEST_END();
}

void test_ldx_im(CPU cpu, MEMORY memory)
{
	int number_of_instructions;

	TEST_START("LDX Immediate");

	cpu_reset(&cpu, &memory);
	memory.data[0xFFFC] = INS_LDX_IM;
	memory.data[0xFFFD] = 0x12;
	number_of_instructions = instruction_execute(&cpu, &memory);

	EXPECT_EQ(cpu.x, 0x12);
	EXPECT_EQ(number_of_instructions, 2);
	EXPECT_EQ(cpu.z, 0);
	EXPECT_EQ(cpu.n, 0);
	TEST_END();

	TEST_START("LDX Immediate - negative");

	cpu_reset(&cpu, &memory);
	memory.data[0xFFFC] = INS_LDX_IM;
	memory.data[0xFFFD] = 0x42;
	number_of_instructions = instruction_execute(&cpu, &memory);

	EXPECT_EQ(cpu.x, 0x42);
	EXPECT_EQ(number_of_instructions, 2);
	EXPECT_EQ(cpu.z, 0);
	EXPECT_EQ(cpu.n, 1);
	TEST_END();

	TEST_START("LDX Immediate - zero");

	cpu_reset(&cpu, &memory);
	memory.data[0xFFFC] = INS_LDX_IM;
	memory.data[0xFFFD] = 0x0;
	number_of_instructions = instruction_execute(&cpu, &memory);

	EXPECT_EQ(cpu.x, 0x0);
	EXPECT_EQ(number_of_instructions, 2);
	EXPECT_EQ(cpu.z, 1);
	EXPECT_EQ(cpu.n, 0);
	TEST_END();
}

void test_ldx_zp(CPU cpu, MEMORY memory)
{
	int number_of_instructions;
	TEST_START("LDX Zero page");

	cpu_reset(&cpu, &memory);
	memory.data[0xFFFC] = INS_LDX_ZP;
	memory.data[0xFFFD] = 0x42;
	memory.data[0x42]	= 0x12;
	number_of_instructions = instruction_execute(&cpu, &memory);

	EXPECT_EQ(cpu.x, 0x12);
	EXPECT_EQ(number_of_instructions, 3);
	EXPECT_EQ(cpu.z, 0);
	EXPECT_EQ(cpu.n, 0);

	TEST_END();

	TEST_START("LDX Zero page - negative");

	cpu_reset(&cpu, &memory);
	memory.data[0xFFFC] = INS_LDX_ZP;
	memory.data[0xFFFD] = 0x42;
	memory.data[0x42]	= 0x42;
	number_of_instructions = instruction_execute(&cpu, &memory);

	EXPECT_EQ(cpu.x, 0x42);
	EXPECT_EQ(number_of_instructions, 3);
	EXPECT_EQ(cpu.z, 0);
	EXPECT_EQ(cpu.n, 1);

	TEST_END();

	TEST_START("LDX Zero page - zero");

	cpu_reset(&cpu, &memory);
	memory.data[0xFFFC] = INS_LDX_ZP;
	memory.data[0xFFFD] = 0x42;
	memory.data[0x42]	= 0x0;
	number_of_instructions = instruction_execute(&cpu, &memory);

	EXPECT_EQ(cpu.x, 0x0);
	EXPECT_EQ(number_of_instructions, 3);
	EXPECT_EQ(cpu.z, 1);
	EXPECT_EQ(cpu.n, 0);

	TEST_END();
}

void test_ldx_zpy(CPU cpu, MEMORY memory)
{
	int number_of_instructions;

	TEST_START("LDX  Zero page Y");

	cpu_reset(&cpu, &memory);
	cpu.y = 0x7;
	memory.data[0xFFFC] = INS_LDX_ZPY;
	memory.data[0xFFFD] = 0x42;
	memory.data[0x49] = 0x13;
	number_of_instructions = instruction_execute(&cpu, &memory);

	EXPECT_EQ(cpu.x, 0x13);
	EXPECT_EQ(number_of_instructions, 4);
	EXPECT_EQ(cpu.z, 0);
	EXPECT_EQ(cpu.n, 0);

	TEST_END();

	TEST_START("LDX  Zero page Y - negative");

	cpu_reset(&cpu, &memory);
	cpu.y = 0x7;
	memory.data[0xFFFC] = INS_LDX_ZPY;
	memory.data[0xFFFD] = 0x42;
	memory.data[0x49] = 0x42;
	number_of_instructions = instruction_execute(&cpu, &memory);

	EXPECT_EQ(cpu.x, 0x42);
	EXPECT_EQ(number_of_instructions, 4);
	EXPECT_EQ(cpu.z, 0);
	EXPECT_EQ(cpu.n, 1);

	TEST_END();

	TEST_START("LDX  Zero page Y - zero");

	cpu_reset(&cpu, &memory);
	cpu.y = 0x7;
	memory.data[0xFFFC] = INS_LDX_ZPY;
	memory.data[0xFFFD] = 0x42;
	memory.data[0x49] = 0x0;
	number_of_instructions = instruction_execute(&cpu, &memory);

	EXPECT_EQ(cpu.x, 0x0);
	EXPECT_EQ(number_of_instructions, 4);
	EXPECT_EQ(cpu.z, 1);
	EXPECT_EQ(cpu.n, 0);

	TEST_END();
}

void test_ldx_abs(CPU cpu, MEMORY memory)
{
	int number_of_instructions;

	TEST_START("LDX Absolute");

	cpu_reset(&cpu, &memory);
	memory.data[0xFFFC] = INS_LDX_ABS;
	memory.data[0xFFFD] = 0x42;
	memory.data[0xFFFE] = 0x12;
	memory.data[0x1242] = 0x15;
	number_of_instructions = instruction_execute(&cpu, &memory);

	EXPECT_EQ(cpu.x, 0x15);
	EXPECT_EQ(number_of_instructions, 4);
	EXPECT_EQ(cpu.z, 0);
	EXPECT_EQ(cpu.n, 0);

	TEST_END();

	TEST_START("LDX Absolute - negative");

	cpu_reset(&cpu, &memory);
	memory.data[0xFFFC] = INS_LDX_ABS;
	memory.data[0xFFFD] = 0x42;
	memory.data[0xFFFE] = 0x12;
	memory.data[0x1242] = 0x42;
	number_of_instructions = instruction_execute(&cpu, &memory);

	EXPECT_EQ(cpu.x, 0x42);
	EXPECT_EQ(number_of_instructions, 4);
	EXPECT_EQ(cpu.z, 0);
	EXPECT_EQ(cpu.n, 1);

	TEST_END();

	TEST_START("LDX Absolute - zero");

	cpu_reset(&cpu, &memory);
	memory.data[0xFFFC] = INS_LDX_ABS;
	memory.data[0xFFFD] = 0x42;
	memory.data[0xFFFE] = 0x12;
	memory.data[0x1242] = 0x0;
	number_of_instructions = instruction_execute(&cpu, &memory);

	EXPECT_EQ(cpu.x, 0x0);
	EXPECT_EQ(number_of_instructions, 4);
	EXPECT_EQ(cpu.z, 1);
	EXPECT_EQ(cpu.n, 0);

	TEST_END();
}

void test_ldx_absy(CPU cpu, MEMORY memory)
{
	int number_of_instructions;

	TEST_START("LDX Absolute Y");

	cpu_reset(&cpu, &memory);
	cpu.y = 0x3;
	memory.data[0xFFFC] = INS_LDX_ABSY;
	memory.data[0xFFFD] = 0x12;
	memory.data[0xFFFE] = 0x0;
	memory.data[0x15] = 0x15;
	number_of_instructions = instruction_execute(&cpu, &memory);

	EXPECT_EQ(cpu.x, 0x15);
	EXPECT_EQ(number_of_instructions, 4);
	EXPECT_EQ(cpu.z, 0);
	EXPECT_EQ(cpu.n, 0);

	TEST_END();

	TEST_START("LDX Absolute Y - negative");

	cpu_reset(&cpu, &memory);
	cpu.y = 0x3;
	memory.data[0xFFFC] = INS_LDX_ABSY;
	memory.data[0xFFFD] = 0x12;
	memory.data[0xFFFE] = 0x0;
	memory.data[0x15] = 0x42;
	number_of_instructions = instruction_execute(&cpu, &memory);

	EXPECT_EQ(cpu.x, 0x42);
	EXPECT_EQ(number_of_instructions, 4);
	EXPECT_EQ(cpu.z, 0);
	EXPECT_EQ(cpu.n, 1);

	TEST_END();

	TEST_START("LDX Absolute Y - zero");

	cpu_reset(&cpu, &memory);
	cpu.y = 0x3;
	memory.data[0xFFFC] = INS_LDX_ABSY;
	memory.data[0xFFFD] = 0x12;
	memory.data[0xFFFE] = 0x0;
	memory.data[0x15] = 0x0;
	number_of_instructions = instruction_execute(&cpu, &memory);

	EXPECT_EQ(cpu.x, 0x0);
	EXPECT_EQ(number_of_instructions, 4);
	EXPECT_EQ(cpu.z, 1);
	EXPECT_EQ(cpu.n, 0);

	TEST_END();

	TEST_START("LDX Absolute Y page crossed");

	cpu_reset(&cpu, &memory);
	cpu.y = 0xF;
	memory.data[0xFFFC] = INS_LDX_ABSY;
	memory.data[0xFFFD] = 0xFF;
	memory.data[0xFFFE] = 0x0;
	memory.data[0x010E] = 0x15;
	number_of_instructions = instruction_execute(&cpu, &memory);

	EXPECT_EQ(cpu.x, 0x15);
	EXPECT_EQ(number_of_instructions, 5);
	EXPECT_EQ(cpu.z, 0);
	EXPECT_EQ(cpu.n, 0);

	TEST_END();

	TEST_START("LDX Absolute Y page crossed - negative");

	cpu_reset(&cpu, &memory);
	cpu.y = 0xF;
	memory.data[0xFFFC] = INS_LDX_ABSY;
	memory.data[0xFFFD] = 0xFF;
	memory.data[0xFFFE] = 0x0;
	memory.data[0x010E] = 0x42;
	number_of_instructions = instruction_execute(&cpu, &memory);

	EXPECT_EQ(cpu.x, 0x42);
	EXPECT_EQ(number_of_instructions, 5);
	EXPECT_EQ(cpu.z, 0);
	EXPECT_EQ(cpu.n, 1);

	TEST_END();

	TEST_START("LDX Absolute Y page crossed - zero");

	cpu_reset(&cpu, &memory);
	cpu.y = 0xF;
	memory.data[0xFFFC] = INS_LDX_ABSY;
	memory.data[0xFFFD] = 0xFF;
	memory.data[0xFFFE] = 0x0;
	memory.data[0x010E] = 0x0;
	number_of_instructions = instruction_execute(&cpu, &memory);

	EXPECT_EQ(cpu.x, 0x0);
	EXPECT_EQ(number_of_instructions, 5);
	EXPECT_EQ(cpu.z, 1);
	EXPECT_EQ(cpu.n, 0);

	TEST_END();
}

void test_ldy_im(CPU cpu, MEMORY memory)
{
	int number_of_instructions;

	TEST_START("LDY Immediate");

	cpu_reset(&cpu, &memory);
	memory.data[0xFFFC] = INS_LDY_IM;
	memory.data[0xFFFD] = 0x12;
	number_of_instructions = instruction_execute(&cpu, &memory);

	EXPECT_EQ(cpu.y, 0x12);
	EXPECT_EQ(number_of_instructions, 2);
	EXPECT_EQ(cpu.z, 0);
	EXPECT_EQ(cpu.n, 0);
	TEST_END();

	TEST_START("LDY Immediate - negative");

	cpu_reset(&cpu, &memory);
	memory.data[0xFFFC] = INS_LDY_IM;
	memory.data[0xFFFD] = 0x42;
	number_of_instructions = instruction_execute(&cpu, &memory);

	EXPECT_EQ(cpu.y, 0x42);
	EXPECT_EQ(number_of_instructions, 2);
	EXPECT_EQ(cpu.z, 0);
	EXPECT_EQ(cpu.n, 1);
	TEST_END();

	TEST_START("LDY Immediate - zero");

	cpu_reset(&cpu, &memory);
	memory.data[0xFFFC] = INS_LDY_IM;
	memory.data[0xFFFD] = 0x0;
	number_of_instructions = instruction_execute(&cpu, &memory);

	EXPECT_EQ(cpu.y, 0x0);
	EXPECT_EQ(number_of_instructions, 2);
	EXPECT_EQ(cpu.z, 1);
	EXPECT_EQ(cpu.n, 0);
	TEST_END();
}

void test_ldy_zp(CPU cpu, MEMORY memory)
{
	int number_of_instructions;
	TEST_START("LDY Zero page");

	cpu_reset(&cpu, &memory);
	memory.data[0xFFFC] = INS_LDY_ZP;
	memory.data[0xFFFD] = 0x42;
	memory.data[0x42]	= 0x12;
	number_of_instructions = instruction_execute(&cpu, &memory);

	EXPECT_EQ(cpu.y, 0x12);
	EXPECT_EQ(number_of_instructions, 3);
	EXPECT_EQ(cpu.z, 0);
	EXPECT_EQ(cpu.n, 0);

	TEST_END();

	TEST_START("LDY Zero page - negative");

	cpu_reset(&cpu, &memory);
	memory.data[0xFFFC] = INS_LDY_ZP;
	memory.data[0xFFFD] = 0x42;
	memory.data[0x42]	= 0x42;
	number_of_instructions = instruction_execute(&cpu, &memory);

	EXPECT_EQ(cpu.y, 0x42);
	EXPECT_EQ(number_of_instructions, 3);
	EXPECT_EQ(cpu.z, 0);
	EXPECT_EQ(cpu.n, 1);

	TEST_END();

	TEST_START("LDY Zero page - zero");

	cpu_reset(&cpu, &memory);
	memory.data[0xFFFC] = INS_LDY_ZP;
	memory.data[0xFFFD] = 0x42;
	memory.data[0x42]	= 0x0;
	number_of_instructions = instruction_execute(&cpu, &memory);

	EXPECT_EQ(cpu.y, 0x0);
	EXPECT_EQ(number_of_instructions, 3);
	EXPECT_EQ(cpu.z, 1);
	EXPECT_EQ(cpu.n, 0);

	TEST_END();
}

void test_ldy_zpx(CPU cpu, MEMORY memory)
{
	int number_of_instructions;

	TEST_START("LDY  Zero page X");

	cpu_reset(&cpu, &memory);
	cpu.x = 0x7;
	memory.data[0xFFFC] = INS_LDY_ZPX;
	memory.data[0xFFFD] = 0x42;
	memory.data[0x49] = 0x13;
	number_of_instructions = instruction_execute(&cpu, &memory);

	EXPECT_EQ(cpu.y, 0x13);
	EXPECT_EQ(number_of_instructions, 4);
	EXPECT_EQ(cpu.z, 0);
	EXPECT_EQ(cpu.n, 0);

	TEST_END();

	TEST_START("LDY  Zero page X - negative");

	cpu_reset(&cpu, &memory);
	cpu.x = 0x7;
	memory.data[0xFFFC] = INS_LDY_ZPX;
	memory.data[0xFFFD] = 0x42;
	memory.data[0x49] = 0x42;
	number_of_instructions = instruction_execute(&cpu, &memory);

	EXPECT_EQ(cpu.y, 0x42);
	EXPECT_EQ(number_of_instructions, 4);
	EXPECT_EQ(cpu.z, 0);
	EXPECT_EQ(cpu.n, 1);

	TEST_END();

	TEST_START("LDY  Zero page X - zero");

	cpu_reset(&cpu, &memory);
	cpu.x = 0x7;
	memory.data[0xFFFC] = INS_LDY_ZPX;
	memory.data[0xFFFD] = 0x42;
	memory.data[0x49] = 0x0;
	number_of_instructions = instruction_execute(&cpu, &memory);

	EXPECT_EQ(cpu.y, 0x0);
	EXPECT_EQ(number_of_instructions, 4);
	EXPECT_EQ(cpu.z, 1);
	EXPECT_EQ(cpu.n, 0);

	TEST_END();
}

void test_ldy_abs(CPU cpu, MEMORY memory)
{
	int number_of_instructions;

	TEST_START("LDY Absolute");

	cpu_reset(&cpu, &memory);
	memory.data[0xFFFC] = INS_LDY_ABS;
	memory.data[0xFFFD] = 0x42;
	memory.data[0xFFFE] = 0x12;
	memory.data[0x1242] = 0x15;
	number_of_instructions = instruction_execute(&cpu, &memory);

	EXPECT_EQ(cpu.y, 0x15);
	EXPECT_EQ(number_of_instructions, 4);
	EXPECT_EQ(cpu.z, 0);
	EXPECT_EQ(cpu.n, 0);

	TEST_END();

	TEST_START("LDY Absolute - negative");

	cpu_reset(&cpu, &memory);
	memory.data[0xFFFC] = INS_LDY_ABS;
	memory.data[0xFFFD] = 0x42;
	memory.data[0xFFFE] = 0x12;
	memory.data[0x1242] = 0x42;
	number_of_instructions = instruction_execute(&cpu, &memory);

	EXPECT_EQ(cpu.y, 0x42);
	EXPECT_EQ(number_of_instructions, 4);
	EXPECT_EQ(cpu.z, 0);
	EXPECT_EQ(cpu.n, 1);

	TEST_END();

	TEST_START("LDY Absolute - zero");

	cpu_reset(&cpu, &memory);
	memory.data[0xFFFC] = INS_LDY_ABS;
	memory.data[0xFFFD] = 0x42;
	memory.data[0xFFFE] = 0x12;
	memory.data[0x1242] = 0x0;
	number_of_instructions = instruction_execute(&cpu, &memory);

	EXPECT_EQ(cpu.y, 0x0);
	EXPECT_EQ(number_of_instructions, 4);
	EXPECT_EQ(cpu.z, 1);
	EXPECT_EQ(cpu.n, 0);

	TEST_END();
}

void test_ldy_absx(CPU cpu, MEMORY memory)
{
	int number_of_instructions;

	TEST_START("LDY Absolute X");

	cpu_reset(&cpu, &memory);
	cpu.x = 0x3;
	memory.data[0xFFFC] = INS_LDY_ABSX;
	memory.data[0xFFFD] = 0x12;
	memory.data[0xFFFE] = 0x0;
	memory.data[0x15] = 0x15;
	number_of_instructions = instruction_execute(&cpu, &memory);

	EXPECT_EQ(cpu.y, 0x15);
	EXPECT_EQ(number_of_instructions, 4);
	EXPECT_EQ(cpu.z, 0);
	EXPECT_EQ(cpu.n, 0);

	TEST_END();

	TEST_START("LDY Absolute X - negative");

	cpu_reset(&cpu, &memory);
	cpu.x = 0x3;
	memory.data[0xFFFC] = INS_LDY_ABSX;
	memory.data[0xFFFD] = 0x12;
	memory.data[0xFFFE] = 0x0;
	memory.data[0x15] = 0x42;
	number_of_instructions = instruction_execute(&cpu, &memory);

	EXPECT_EQ(cpu.y, 0x42);
	EXPECT_EQ(number_of_instructions, 4);
	EXPECT_EQ(cpu.z, 0);
	EXPECT_EQ(cpu.n, 1);

	TEST_END();

	TEST_START("LDY Absolute X - zero");

	cpu_reset(&cpu, &memory);
	cpu.x = 0x3;
	memory.data[0xFFFC] = INS_LDY_ABSX;
	memory.data[0xFFFD] = 0x12;
	memory.data[0xFFFE] = 0x0;
	memory.data[0x15] = 0x0;
	number_of_instructions = instruction_execute(&cpu, &memory);

	EXPECT_EQ(cpu.y, 0x0);
	EXPECT_EQ(number_of_instructions, 4);
	EXPECT_EQ(cpu.z, 1);
	EXPECT_EQ(cpu.n, 0);

	TEST_END();

	TEST_START("LDY Absolute X page crossed");

	cpu_reset(&cpu, &memory);
	cpu.x = 0xF;
	memory.data[0xFFFC] = INS_LDY_ABSX;
	memory.data[0xFFFD] = 0xFF;
	memory.data[0xFFFE] = 0x0;
	memory.data[0x010E] = 0x15;
	number_of_instructions = instruction_execute(&cpu, &memory);

	EXPECT_EQ(cpu.y, 0x15);
	EXPECT_EQ(number_of_instructions, 5);
	EXPECT_EQ(cpu.z, 0);
	EXPECT_EQ(cpu.n, 0);

	TEST_END();

	TEST_START("LDY Absolute X page crossed - negative");

	cpu_reset(&cpu, &memory);
	cpu.x = 0xF;
	memory.data[0xFFFC] = INS_LDY_ABSX;
	memory.data[0xFFFD] = 0xFF;
	memory.data[0xFFFE] = 0x0;
	memory.data[0x010E] = 0x42;
	number_of_instructions = instruction_execute(&cpu, &memory);

	EXPECT_EQ(cpu.y, 0x42);
	EXPECT_EQ(number_of_instructions, 5);
	EXPECT_EQ(cpu.z, 0);
	EXPECT_EQ(cpu.n, 1);

	TEST_END();

	TEST_START("LDY Absolute X page crossed - zero");

	cpu_reset(&cpu, &memory);
	cpu.x = 0xF;
	memory.data[0xFFFC] = INS_LDY_ABSX;
	memory.data[0xFFFD] = 0xFF;
	memory.data[0xFFFE] = 0x0;
	memory.data[0x010E] = 0x0;
	number_of_instructions = instruction_execute(&cpu, &memory);

	EXPECT_EQ(cpu.y, 0x0);
	EXPECT_EQ(number_of_instructions, 5);
	EXPECT_EQ(cpu.z, 1);
	EXPECT_EQ(cpu.n, 0);

	TEST_END();
}

void test_sta_zp(CPU cpu, MEMORY memory)
{
	int number_of_instructions;

	TEST_START("STA zero page");

	cpu_reset(&cpu, &memory);
	cpu.a = 0x12;
	memory.data[0xFFFC] = INS_STA_ZP;
	memory.data[0xFFFD] = 0x0033;

	number_of_instructions = instruction_execute(&cpu, &memory);

	EXPECT_EQ(cpu.a, memory.data[0x0033]);
	EXPECT_EQ(number_of_instructions, 3);

	TEST_END();
}

void test_sta_zpx(CPU cpu, MEMORY memory)
{
	int number_of_instructions;

	TEST_START("STA zero page X");

	cpu_reset(&cpu, &memory);
	cpu.a = 0x12;
	cpu.x = 0x13;
	memory.data[0xFFFC] = INS_STA_ZPX;
	memory.data[0xFFFD] = 0x0033;

	number_of_instructions = instruction_execute(&cpu, &memory);

	EXPECT_EQ(cpu.a, memory.data[0x33 + 0x13]);
	EXPECT_EQ(number_of_instructions, 4);

	TEST_END();

	TEST_START("STA zero page X - page crossed");

	cpu_reset(&cpu, &memory);
	cpu.a = 0x12;
	cpu.x = 0xFF;
	memory.data[0xFFFC] = INS_STA_ZPX;
	memory.data[0xFFFD] = 0x0033;

	number_of_instructions = instruction_execute(&cpu, &memory);

	EXPECT_EQ(cpu.a, memory.data[0x32]);
	EXPECT_EQ(number_of_instructions, 4);

	TEST_END();
}

void test_sta_abs(CPU cpu, MEMORY memory)
{
	int number_of_instructions;

	TEST_START("STA absolute");

	cpu_reset(&cpu, &memory);

	cpu.a = 0x12;
	memory.data[0xFFFC] = INS_STA_ABS;
	memory.data[0xFFFD] = 0x34;
	memory.data[0xFFFE] = 0x12;

	number_of_instructions = instruction_execute(&cpu, &memory);

	EXPECT_EQ(cpu.a, memory.data[0x1234]);
	EXPECT_EQ(number_of_instructions, 4);

	TEST_END();

}

void test_sta_absx(CPU cpu, MEMORY memory)
{
	int number_of_instructions;

	TEST_START("STA absolute X");

	cpu_reset(&cpu, &memory);

	cpu.x = 0x03;
	cpu.a = 0x12;
	memory.data[0xFFFC] = INS_STA_ABSX;
	memory.data[0xFFFD] = 0x34;
	memory.data[0xFFFE] = 0x12;

	number_of_instructions = instruction_execute(&cpu, &memory);

	EXPECT_EQ(cpu.a, memory.data[0x1234 + cpu.x]);
	EXPECT_EQ(number_of_instructions, 5);

	TEST_END();
}

void test_sta_absy(CPU cpu, MEMORY memory)
{
	int number_of_instructions;

	TEST_START("STA absolute Y");

	cpu_reset(&cpu, &memory);

	cpu.y = 0x03;
	cpu.a = 0x12;
	memory.data[0xFFFC] = INS_STA_ABSY;
	memory.data[0xFFFD] = 0x34;
	memory.data[0xFFFE] = 0x12;

	number_of_instructions = instruction_execute(&cpu, &memory);

	EXPECT_EQ(cpu.a, memory.data[0x1234 + cpu.y]);
	EXPECT_EQ(number_of_instructions, 5);

	TEST_END();
}

void test_sta_indx(CPU cpu, MEMORY memory)
{
	int number_of_instructions;

	TEST_START("STA Indirect X");

	cpu_reset(&cpu, &memory);
	cpu.a = 0x12;
	cpu.x = 0x04;
	memory.data[0xFFFC] = INS_STA_INDX;
	memory.data[0xFFFD] = 0x02;
	memory.data[0x0006] = 0x00;
	memory.data[0x0007] = 0x80;

	number_of_instructions = instruction_execute(&cpu, &memory);

	EXPECT_EQ(cpu.a, memory.data[0x8000]);
	EXPECT_EQ(number_of_instructions, 6);

	TEST_END();
}

void test_sta_indy(CPU cpu, MEMORY memory)
{
	int number_of_instructions;

	TEST_START("STA Indirect X");

	cpu_reset(&cpu, &memory);
	cpu.a = 0x12;
	cpu.y = 0x04;
	memory.data[0xFFFC] = INS_STA_INDY;
	memory.data[0xFFFD] = 0x02;
	memory.data[0x0002] = 0x00;
	memory.data[0x0003] = 0x80;

	number_of_instructions = instruction_execute(&cpu, &memory);

	EXPECT_EQ(cpu.a, memory.data[0x8000 + cpu.y]);
	EXPECT_EQ(number_of_instructions, 6);

	TEST_END();
}

void test_stx_zp(CPU cpu, MEMORY memory)
{
	int number_of_instructions;

	TEST_START("STX zero page");

	cpu_reset(&cpu, &memory);
	cpu.x = 0x12;
	memory.data[0xFFFC] = INS_STX_ZP;
	memory.data[0xFFFD] = 0x0033;

	number_of_instructions = instruction_execute(&cpu, &memory);

	EXPECT_EQ(cpu.x, memory.data[0x0033]);
	EXPECT_EQ(number_of_instructions, 3);

	TEST_END();
}

void test_stx_zpy(CPU cpu, MEMORY memory)
{
	int number_of_instructions;

	TEST_START("STX zero page Y");

	cpu_reset(&cpu, &memory);
	cpu.x = 0x12;
	cpu.y = 0x13;
	memory.data[0xFFFC] = INS_STX_ZPY;
	memory.data[0xFFFD] = 0x0033;

	number_of_instructions = instruction_execute(&cpu, &memory);

	EXPECT_EQ(cpu.x, memory.data[0x33 + 0x13]);
	EXPECT_EQ(number_of_instructions, 4);

	TEST_END();

	TEST_START("STX zero page Y - page crossed");

	cpu_reset(&cpu, &memory);
	cpu.x = 0x12;
	cpu.y = 0xFF;
	memory.data[0xFFFC] = INS_STX_ZPY;
	memory.data[0xFFFD] = 0x0033;

	number_of_instructions = instruction_execute(&cpu, &memory);

	EXPECT_EQ(cpu.x, memory.data[0x32]);
	EXPECT_EQ(number_of_instructions, 4);

	TEST_END();
}

void test_stx_abs(CPU cpu, MEMORY memory)
{
	int number_of_instructions;

	TEST_START("STX absolute");

	cpu_reset(&cpu, &memory);

	cpu.x = 0x12;
	memory.data[0xFFFC] = INS_STX_ABS;
	memory.data[0xFFFD] = 0x34;
	memory.data[0xFFFE] = 0x12;

	number_of_instructions = instruction_execute(&cpu, &memory);

	EXPECT_EQ(cpu.x, memory.data[0x1234]);
	EXPECT_EQ(number_of_instructions, 4);

	TEST_END();

}

void test_sty_zp(CPU cpu, MEMORY memory)
{
	int number_of_instructions;

	TEST_START("STY zero page");

	cpu_reset(&cpu, &memory);
	cpu.y = 0x12;
	memory.data[0xFFFC] = INS_STY_ZP;
	memory.data[0xFFFD] = 0x0033;

	number_of_instructions = instruction_execute(&cpu, &memory);

	EXPECT_EQ(cpu.y, memory.data[0x0033]);
	EXPECT_EQ(number_of_instructions, 3);

	TEST_END();
}

void test_sty_zpx(CPU cpu, MEMORY memory)
{
	int number_of_instructions;

	TEST_START("STY zero page X");

	cpu_reset(&cpu, &memory);
	cpu.y = 0x12;
	cpu.x = 0x13;
	memory.data[0xFFFC] = INS_STY_ZPX;
	memory.data[0xFFFD] = 0x0033;

	number_of_instructions = instruction_execute(&cpu, &memory);

	EXPECT_EQ(cpu.y, memory.data[0x33 + 0x13]);
	EXPECT_EQ(number_of_instructions, 4);

	TEST_END();

	TEST_START("STY zero page X - page crossed");

	cpu_reset(&cpu, &memory);
	cpu.y = 0x12;
	cpu.x = 0xFF;
	memory.data[0xFFFC] = INS_STY_ZPX;
	memory.data[0xFFFD] = 0x0033;

	number_of_instructions = instruction_execute(&cpu, &memory);

	EXPECT_EQ(cpu.y, memory.data[0x32]);
	EXPECT_EQ(number_of_instructions, 4);

	TEST_END();
}

void test_sty_abs(CPU cpu, MEMORY memory)
{
	int number_of_instructions;

	TEST_START("STY absolute");

	cpu_reset(&cpu, &memory);

	cpu.y = 0x12;
	memory.data[0xFFFC] = INS_STY_ABS;
	memory.data[0xFFFD] = 0x34;
	memory.data[0xFFFE] = 0x12;

	number_of_instructions = instruction_execute(&cpu, &memory);

	EXPECT_EQ(cpu.y, memory.data[0x1234]);
	EXPECT_EQ(number_of_instructions, 4);

	TEST_END();

}

void test_tax(CPU cpu, MEMORY memory)
{
	int number_of_instructions;

	TEST_START("TAX");

	cpu_reset(&cpu, &memory);

	cpu.a = 0x12;
	memory.data[0xFFFC] = INS_TAX;

	number_of_instructions = instruction_execute(&cpu, &memory);

	EXPECT_EQ(cpu.x, cpu.a);
	EXPECT_EQ(number_of_instructions, 2);

	TEST_END();

	TEST_START("TAX - zero");

	cpu_reset(&cpu, &memory);

	cpu.a = 0x0;
	memory.data[0xFFFC] = INS_TAX;

	number_of_instructions = instruction_execute(&cpu, &memory);

	EXPECT_EQ(cpu.x, cpu.a);
	EXPECT_EQ(number_of_instructions, 2);
	EXPECT_TRUE(cpu.z);

	TEST_END();

	TEST_START("TAX - negative");

	cpu_reset(&cpu, &memory);

	cpu.a = 0x42;
	memory.data[0xFFFC] = INS_TAX;

	number_of_instructions = instruction_execute(&cpu, &memory);

	EXPECT_EQ(cpu.x, cpu.a);
	EXPECT_EQ(number_of_instructions, 2);
	EXPECT_TRUE(cpu.n);

	TEST_END();
}

void test_tay(CPU cpu, MEMORY memory)
{
	int number_of_instructions;

	TEST_START("TAY");

	cpu_reset(&cpu, &memory);

	cpu.a = 0x12;
	memory.data[0xFFFC] = INS_TAY;

	number_of_instructions = instruction_execute(&cpu, &memory);

	EXPECT_EQ(cpu.y, cpu.a);
	EXPECT_EQ(number_of_instructions, 2);

	TEST_END();

	TEST_START("TAY - zero");

	cpu_reset(&cpu, &memory);

	cpu.a = 0x0;
	memory.data[0xFFFC] = INS_TAY;

	number_of_instructions = instruction_execute(&cpu, &memory);

	EXPECT_EQ(cpu.y, cpu.a);
	EXPECT_EQ(number_of_instructions, 2);
	EXPECT_TRUE(cpu.z);

	TEST_END();

	TEST_START("TAX - negative");

	cpu_reset(&cpu, &memory);

	cpu.a = 0x42;
	memory.data[0xFFFC] = INS_TAY;

	number_of_instructions = instruction_execute(&cpu, &memory);

	EXPECT_EQ(cpu.y, cpu.a);
	EXPECT_EQ(number_of_instructions, 2);
	EXPECT_TRUE(cpu.n);

	TEST_END();
}

void test_txa(CPU cpu, MEMORY memory)
{
	int number_of_instructions;

	TEST_START("TXA");

	cpu_reset(&cpu, &memory);

	cpu.x = 0x12;
	memory.data[0xFFFC] = INS_TXA;

	number_of_instructions = instruction_execute(&cpu, &memory);

	EXPECT_EQ(cpu.a, cpu.x);
	EXPECT_EQ(number_of_instructions, 2);

	TEST_END();

	TEST_START("TXA - zero");

	cpu_reset(&cpu, &memory);

	cpu.x = 0x0;
	memory.data[0xFFFC] = INS_TXA;

	number_of_instructions = instruction_execute(&cpu, &memory);

	EXPECT_EQ(cpu.a, cpu.x);
	EXPECT_EQ(number_of_instructions, 2);
	EXPECT_TRUE(cpu.z);

	TEST_END();

	TEST_START("TXA - negative");

	cpu_reset(&cpu, &memory);

	cpu.x = 0x42;
	memory.data[0xFFFC] = INS_TXA;

	number_of_instructions = instruction_execute(&cpu, &memory);

	EXPECT_EQ(cpu.a, cpu.x);
	EXPECT_EQ(number_of_instructions, 2);
	EXPECT_TRUE(cpu.n);

	TEST_END();
}

void test_tya(CPU cpu, MEMORY memory)
{
	int number_of_instructions;

	TEST_START("TYA");

	cpu_reset(&cpu, &memory);

	cpu.y = 0x12;
	memory.data[0xFFFC] = INS_TYA;

	number_of_instructions = instruction_execute(&cpu, &memory);

	EXPECT_EQ(cpu.a, cpu.y);
	EXPECT_EQ(number_of_instructions, 2);

	TEST_END();

	TEST_START("TYA - zero");

	cpu_reset(&cpu, &memory);

	cpu.y = 0x0;
	memory.data[0xFFFC] = INS_TYA;

	number_of_instructions = instruction_execute(&cpu, &memory);

	EXPECT_EQ(cpu.a, cpu.y);
	EXPECT_EQ(number_of_instructions, 2);
	EXPECT_TRUE(cpu.z);

	TEST_END();

	TEST_START("TYA - negative");

	cpu_reset(&cpu, &memory);

	cpu.y = 0x42;
	memory.data[0xFFFC] = INS_TYA;

	number_of_instructions = instruction_execute(&cpu, &memory);

	EXPECT_EQ(cpu.a, cpu.y);
	EXPECT_EQ(number_of_instructions, 2);
	EXPECT_TRUE(cpu.n);

	TEST_END();
}

void test_tsx(CPU cpu, MEMORY memory)
{
	int number_of_instructions;

	TEST_START("TSX");

	cpu_reset(&cpu, &memory);

	cpu.sp = 0x12;
	memory.data[0xFFFC] = INS_TSX;

	number_of_instructions = instruction_execute(&cpu, &memory);

	EXPECT_EQ(cpu.sp, cpu.x);
	EXPECT_EQ(number_of_instructions, 2);

	TEST_END();

	TEST_START("TSX - zero");

	cpu_reset(&cpu, &memory);

	cpu.sp = 0x0;
	memory.data[0xFFFC] = INS_TSX;

	number_of_instructions = instruction_execute(&cpu, &memory);

	EXPECT_EQ(cpu.sp, cpu.x);
	EXPECT_EQ(number_of_instructions, 2);
	EXPECT_TRUE(cpu.z);

	TEST_END();

	TEST_START("TSX - negative");

	cpu_reset(&cpu, &memory);

	cpu.sp = 0x42;
	memory.data[0xFFFC] = INS_TSX;

	number_of_instructions = instruction_execute(&cpu, &memory);

	EXPECT_EQ(cpu.sp, cpu.x);
	EXPECT_EQ(number_of_instructions, 2);
	EXPECT_TRUE(cpu.n);

	TEST_END();
}

void test_txs(CPU cpu, MEMORY memory)
{
	int number_of_instructions;

	TEST_START("TXS");

	cpu_reset(&cpu, &memory);

	cpu.x = 0x12;
	memory.data[0xFFFC] = INS_TXS;

	number_of_instructions = instruction_execute(&cpu, &memory);

	EXPECT_EQ(cpu.sp, cpu.x);
	EXPECT_EQ(number_of_instructions, 2);

	TEST_END();
}

void test_pha(CPU cpu, MEMORY memory)
{
	int number_of_instructions;

	TEST_START("PHA");

	cpu_reset(&cpu, &memory);

	cpu.a = 0x12;
	memory.data[0xFFFC] = INS_PHA;

	number_of_instructions = instruction_execute(&cpu, &memory);

	EXPECT_EQ(cpu.a, memory.data[STACK_OFFSET + 0xFF]);
	EXPECT_EQ(number_of_instructions, 3);

	TEST_END();
}

void test_pla(CPU cpu, MEMORY memory)
{
	int number_of_instructions;

	TEST_START("PLA");

	cpu_reset(&cpu, &memory);

	memory.data[0xFFFC] = INS_PLA;
	memory.data[STACK_OFFSET + cpu.sp] = 0x12;

	number_of_instructions = instruction_execute(&cpu, &memory);

	EXPECT_EQ(cpu.a, memory.data[STACK_OFFSET + 0xFF]);
	EXPECT_EQ(number_of_instructions, 3);

	TEST_END();
}
