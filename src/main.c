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
void test_php(CPU cpu, MEMORY memory);
void test_plp(CPU cpu, MEMORY memory);

/* Tests for logical operatiosn */
/* AND */
void test_and_im(CPU cpu, MEMORY memory);
void test_and_zp(CPU cpu, MEMORY memory);
void test_and_zpx(CPU cpu, MEMORY memory);
void test_and_abs(CPU cpu, MEMORY memory);
void test_and_absx(CPU cpu, MEMORY memory);
void test_and_absy(CPU cpu, MEMORY memory);
void test_and_indx(CPU cpu, MEMORY memory);
void test_and_indy(CPU cpu, MEMORY memory);

/* EOR */
void test_eor_im(CPU cpu, MEMORY memory);
void test_eor_zp(CPU cpu, MEMORY memory);
void test_eor_zpx(CPU cpu, MEMORY memory);
void test_eor_abs(CPU cpu, MEMORY memory);
void test_eor_absx(CPU cpu, MEMORY memory);
void test_eor_absy(CPU cpu, MEMORY memory);
void test_eor_indx(CPU cpu, MEMORY memory);
void test_eor_indy(CPU cpu, MEMORY memory);

/* ORA */
void test_ora_im(CPU cpu, MEMORY memory);
void test_ora_zp(CPU cpu, MEMORY memory);
void test_ora_zpx(CPU cpu, MEMORY memory);
void test_ora_abs(CPU cpu, MEMORY memory);
void test_ora_absx(CPU cpu, MEMORY memory);

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
	test_plp(cpu, memory);
	test_php(cpu, memory);

	test_and_im(cpu, memory);
	test_and_zp(cpu, memory);
	test_and_zpx(cpu, memory);
	test_and_abs(cpu, memory);
	test_and_absx(cpu, memory);
	test_and_absy(cpu, memory);
	test_and_indx(cpu, memory);
	test_and_indy(cpu, memory);

	test_eor_im(cpu, memory);
	test_eor_zp(cpu, memory);
	test_eor_zpx(cpu, memory);
	test_eor_abs(cpu, memory);
	test_eor_absx(cpu, memory);
	test_eor_absy(cpu, memory);
	test_eor_indx(cpu, memory);
	test_eor_indy(cpu, memory);

	test_ora_im(cpu, memory);
	test_ora_zp(cpu, memory);
	test_ora_zpx(cpu, memory);
	test_ora_abs(cpu, memory);
	test_ora_absx(cpu, memory);

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

	TEST_START("LDA Zero page X - zero");

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
	cpu.sp--;

	number_of_instructions = instruction_execute(&cpu, &memory);

	EXPECT_EQ(cpu.a, memory.data[STACK_OFFSET + 0xFF]);
	EXPECT_EQ(number_of_instructions, 4);

	TEST_END();

	TEST_START("PLA - negative value");

	cpu_reset(&cpu, &memory);

	memory.data[0xFFFC] = INS_PLA;
	memory.data[STACK_OFFSET + cpu.sp] = 0x42;
	cpu.sp--;

	number_of_instructions = instruction_execute(&cpu, &memory);

	EXPECT_EQ(cpu.a, memory.data[STACK_OFFSET + 0xFF]);
	EXPECT_EQ(number_of_instructions, 4);
	EXPECT_TRUE(cpu.n);

	TEST_END();

	TEST_START("PLA - zero value");

	cpu_reset(&cpu, &memory);

	memory.data[0xFFFC] = INS_PLA;
	memory.data[STACK_OFFSET + cpu.sp] = 0x0;
	cpu.sp--;

	number_of_instructions = instruction_execute(&cpu, &memory);

	EXPECT_EQ(cpu.a, memory.data[STACK_OFFSET + 0xFF]);
	EXPECT_EQ(number_of_instructions, 4);
	EXPECT_TRUE(cpu.z);

	TEST_END();
}

void test_plp(CPU cpu, MEMORY memory)
{
	int number_of_instructions;

	TEST_START("PLP - All FALSE");

	cpu_reset(&cpu, &memory);

	memory.data[0xFFFC] = INS_PLP;
	memory.data[STACK_OFFSET + cpu.sp] = 0x0;
	cpu.sp--;

	number_of_instructions = instruction_execute(&cpu, &memory);

	EXPECT_FALSE(cpu.c);
	EXPECT_FALSE(cpu.z);
	EXPECT_FALSE(cpu.i);
	EXPECT_FALSE(cpu.d);
	EXPECT_FALSE(cpu.b);
	EXPECT_FALSE(cpu.v);
	EXPECT_FALSE(cpu.n);
	EXPECT_EQ(number_of_instructions, 4);

	TEST_END();

	TEST_START("PLP - All TRUE");

	cpu_reset(&cpu, &memory);

	memory.data[0xFFFC] = INS_PLP;
	memory.data[STACK_OFFSET + cpu.sp] = 0xFF;
	cpu.sp--;

	number_of_instructions = instruction_execute(&cpu, &memory);

	EXPECT_TRUE(cpu.c);
	EXPECT_TRUE(cpu.z);
	EXPECT_TRUE(cpu.i);
	EXPECT_TRUE(cpu.d);
	EXPECT_TRUE(cpu.b);
	EXPECT_TRUE(cpu.v);
	EXPECT_TRUE(cpu.n);
	EXPECT_EQ(number_of_instructions, 4);

	TEST_END();
}

void test_php(CPU cpu, MEMORY memory)
{
	int number_of_instructions;

	TEST_START("PHP - All FALSE");

	cpu_reset(&cpu, &memory);

	cpu.c = 0;
	cpu.z = 0;
	cpu.i = 0;
	cpu.d = 0;
	cpu.b = 0;
	cpu.v = 0;
	cpu.n = 0;

	memory.data[0xFFFC] = INS_PHP;
	memory.data[0xFFFD] = 0x0;

	number_of_instructions = instruction_execute(&cpu, &memory);

	EXPECT_EQ(memory.data[0xFFFD], 0);
	EXPECT_EQ(number_of_instructions, 3);

	TEST_END();

	TEST_START("PHP - All TRUE");

	cpu_reset(&cpu, &memory);

	cpu.c = 1;
	cpu.z = 1;
	cpu.i = 1;
	cpu.d = 1;
	cpu.b = 1;
	cpu.v = 1;
	cpu.n = 1;

	memory.data[0xFFFC] = INS_PHP;
	memory.data[0xFFFD] = 0xF;

	number_of_instructions = instruction_execute(&cpu, &memory);

	EXPECT_EQ(memory.data[0xFFFD], 0xF);
	EXPECT_EQ(number_of_instructions, 3);

	TEST_END();
}

void test_and_im(CPU cpu, MEMORY memory)
{
	int number_of_instructions;

	TEST_START("AND - IMMEDIATE");

	cpu_reset(&cpu, &memory);

	cpu.a = 0x12;
	memory.data[0xFFFC] = INS_AND_IM;
	memory.data[0xFFFD] = 0x12;

	number_of_instructions = instruction_execute(&cpu, &memory);

	EXPECT_EQ(cpu.a, 0x12);
	EXPECT_EQ(number_of_instructions, 2);

	cpu_reset(&cpu, &memory);

	cpu.a = 0x5;
	memory.data[0xFFFC] = INS_AND_IM;
	memory.data[0xFFFD] = 0x3;

	number_of_instructions = instruction_execute(&cpu, &memory);

	EXPECT_EQ(cpu.a, 0x1);
	EXPECT_EQ(number_of_instructions, 2);

	TEST_END();
}

void test_and_zp(CPU cpu, MEMORY memory)
{
	int number_of_instructions;

	TEST_START("AND ZP - NOT A MATCH");

	cpu_reset(&cpu, &memory);

	cpu.a = 0x5;
	memory.data[0xFFFC] = INS_AND_ZP;
	memory.data[0xFFFD] = 0x42;
	memory.data[0x42] = 0x03;

	number_of_instructions = instruction_execute(&cpu, &memory);

	EXPECT_EQ(number_of_instructions, 3);
	EXPECT_EQ(cpu.a, 0x1);

	TEST_END();

	TEST_START("AND ZP - MATCH");

	cpu_reset(&cpu, &memory);

	cpu.a = 0x12;
	memory.data[0xFFFC] = INS_AND_ZP;
	memory.data[0xFFFD] = 0x42;
	memory.data[0x42] = 0x12;

	number_of_instructions = instruction_execute(&cpu, &memory);

	EXPECT_EQ(number_of_instructions, 3);
	EXPECT_EQ(cpu.a, 0x12);

	TEST_END();

	TEST_START("AND ZP - NO SAME BITS");

	cpu_reset(&cpu, &memory);

	cpu.a = 0x12;
	memory.data[0xFFFC] = INS_AND_ZP;
	memory.data[0xFFFD] = 0x42;
	memory.data[0x42] = 0x00;

	number_of_instructions = instruction_execute(&cpu, &memory);

	EXPECT_EQ(number_of_instructions, 3);
	EXPECT_EQ(cpu.a, 0x0);

	TEST_END();
}

void test_and_zpx(CPU cpu, MEMORY memory)
{
	int number_of_instructions;

	TEST_START("AND ZPX - NOT A MATCH");

	cpu_reset(&cpu, &memory);

	cpu.x = 0x15;
	cpu.a = 0x5;
	memory.data[0xFFFC] = INS_AND_ZPX;
	memory.data[0xFFFD] = 0x42;
	memory.data[(0x42 + cpu.x)] = 0x3;

	number_of_instructions = instruction_execute(&cpu, &memory);

	EXPECT_EQ(number_of_instructions, 4);
	EXPECT_EQ(cpu.a, 0x1);

	TEST_END();

	TEST_START("AND ZPX - MATCH");

	cpu_reset(&cpu, &memory);

	cpu.x = 0x15;
	cpu.a = 0x12;
	memory.data[0xFFFC] = INS_AND_ZPX;
	memory.data[0xFFFD] = 0x42;
	memory.data[(0x42 + cpu.x)] = 0x12;

	number_of_instructions = instruction_execute(&cpu, &memory);

	EXPECT_EQ(number_of_instructions, 4);
	EXPECT_EQ(cpu.a, 0x12);

	TEST_END();

	TEST_START("AND ZPX - NOT A MATCH");

	cpu_reset(&cpu, &memory);

	cpu.x = 0x15;
	cpu.a = 0x12;
	memory.data[0xFFFC] = INS_AND_ZPX;
	memory.data[0xFFFD] = 0x42;
	memory.data[(0x42 + cpu.x)] = 0x0;

	number_of_instructions = instruction_execute(&cpu, &memory);

	EXPECT_EQ(number_of_instructions, 4);
	EXPECT_EQ(cpu.a, 0x0);


	TEST_END();
}

void test_and_abs(CPU cpu, MEMORY memory)
{
	int number_of_instructions;

	TEST_START("AND ABS - NOT A MATCH");

	cpu_reset(&cpu, &memory);

	cpu.a = 0x5;
	memory.data[0xFFFC] = INS_AND_ABS;
	memory.data[0xFFFD] = 0x34;
	memory.data[0xFFFE] = 0x12;
	memory.data[0x1234] = 0x3;

	number_of_instructions = instruction_execute(&cpu, &memory);

	EXPECT_EQ(number_of_instructions, 4);
	EXPECT_EQ(cpu.a, 0x1);

	TEST_END();

	TEST_START("AND ABS - MATCH");

	cpu_reset(&cpu, &memory);

	cpu.a = 0x5;
	memory.data[0xFFFC] = INS_AND_ABS;
	memory.data[0xFFFD] = 0x34;
	memory.data[0xFFFE] = 0x12;
	memory.data[0x1234] = 0x3;

	number_of_instructions = instruction_execute(&cpu, &memory);

	EXPECT_EQ(number_of_instructions, 4);
	EXPECT_EQ(cpu.a, 0x1);

	TEST_END();

	TEST_START("AND ABS - NO EQAUL BITS");

	cpu_reset(&cpu, &memory);

	cpu.a = 0x5;
	memory.data[0xFFFC] = INS_AND_ABS;
	memory.data[0xFFFD] = 0x34;
	memory.data[0xFFFE] = 0x12;
	memory.data[0x1234] = 0x3;

	number_of_instructions = instruction_execute(&cpu, &memory);

	EXPECT_EQ(number_of_instructions, 4);
	EXPECT_EQ(cpu.a, 0x1);

	TEST_END();
}

void test_and_absx(CPU cpu, MEMORY memory)
{

	int number_of_instructions;

	TEST_START("AND ABS - NOT A MATCH");

	cpu_reset(&cpu, &memory);

	cpu.a = 0x5;
	cpu.x = 0x15;
	memory.data[0xFFFC] = INS_AND_ABSX;
	memory.data[0xFFFD] = 0x34;
	memory.data[0xFFFE] = 0x12;
	memory.data[(0x1234 + cpu.x)] = 0x3;

	number_of_instructions = instruction_execute(&cpu, &memory);

	EXPECT_EQ(number_of_instructions, 4);
	EXPECT_EQ(cpu.a, 0x1);

	TEST_END();

	TEST_START("AND ABS - MATCH");

	cpu_reset(&cpu, &memory);

	cpu.a = 0x12;
	cpu.x = 0x15;
	memory.data[0xFFFC] = INS_AND_ABSX;
	memory.data[0xFFFD] = 0x34;
	memory.data[0xFFFE] = 0x12;
	memory.data[(0x1234 + cpu.x)] = 0x12;

	number_of_instructions = instruction_execute(&cpu, &memory);

	EXPECT_EQ(number_of_instructions, 4);
	EXPECT_EQ(cpu.a, 0x12);

	TEST_END();

	TEST_START("AND ABS - NO EQAUL BITS");

	cpu_reset(&cpu, &memory);

	cpu.a = 0x5;
	cpu.x = 0x15;
	memory.data[0xFFFC] = INS_AND_ABSX;
	memory.data[0xFFFD] = 0x34;
	memory.data[0xFFFE] = 0x12;
	memory.data[(0x1234 + cpu.x)] = 0x0;

	number_of_instructions = instruction_execute(&cpu, &memory);

	EXPECT_EQ(number_of_instructions, 4);
	EXPECT_EQ(cpu.a, 0x0);

	TEST_END();

	TEST_START("AND ABS - PAGE CROSSED");

	cpu_reset(&cpu, &memory);

	cpu.a = 0x5;
	cpu.x = 0x15;
	memory.data[0xFFFC] = INS_AND_ABSX;
	memory.data[0xFFFD] = 0xFF;
	memory.data[0xFFFE] = 0x00;
	memory.data[(0x00FF + cpu.x)] = 0x3;

	number_of_instructions = instruction_execute(&cpu, &memory);

	EXPECT_EQ(number_of_instructions, 5);
	EXPECT_EQ(cpu.a, 0x1);

	TEST_END();
}

void test_and_absy(CPU cpu, MEMORY memory)
{

	int number_of_instructions;

	TEST_START("AND ABS - NOT A MATCH");

	cpu_reset(&cpu, &memory);

	cpu.a = 0x5;
	cpu.y = 0x15;
	memory.data[0xFFFC] = INS_AND_ABSY;
	memory.data[0xFFFD] = 0x34;
	memory.data[0xFFFE] = 0x12;
	memory.data[(0x1234 + cpu.y)] = 0x3;

	number_of_instructions = instruction_execute(&cpu, &memory);

	EXPECT_EQ(number_of_instructions, 4);
	EXPECT_EQ(cpu.a, 0x1);

	TEST_END();

	TEST_START("AND ABS - MATCH");

	cpu_reset(&cpu, &memory);

	cpu.a = 0x12;
	cpu.y = 0x15;
	memory.data[0xFFFC] = INS_AND_ABSY;
	memory.data[0xFFFD] = 0x34;
	memory.data[0xFFFE] = 0x12;
	memory.data[(0x1234 + cpu.y)] = 0x12;

	number_of_instructions = instruction_execute(&cpu, &memory);

	EXPECT_EQ(number_of_instructions, 4);
	EXPECT_EQ(cpu.a, 0x12);

	TEST_END();

	TEST_START("AND ABS - NO EQAUL BITS");

	cpu_reset(&cpu, &memory);

	cpu.a = 0x5;
	cpu.y = 0x15;
	memory.data[0xFFFC] = INS_AND_ABSY;
	memory.data[0xFFFD] = 0x34;
	memory.data[0xFFFE] = 0x12;
	memory.data[(0x1234 + cpu.y)] = 0x0;

	number_of_instructions = instruction_execute(&cpu, &memory);

	EXPECT_EQ(number_of_instructions, 4);
	EXPECT_EQ(cpu.a, 0x0);

	TEST_END();

	TEST_START("AND ABS - PAGE CROSSED");

	cpu_reset(&cpu, &memory);

	cpu.a = 0x5;
	cpu.y = 0x15;
	memory.data[0xFFFC] = INS_AND_ABSY;
	memory.data[0xFFFD] = 0xFF;
	memory.data[0xFFFE] = 0x00;
	memory.data[(0x00FF + cpu.y)] = 0x3;

	number_of_instructions = instruction_execute(&cpu, &memory);

	EXPECT_EQ(number_of_instructions, 5);
	EXPECT_EQ(cpu.a, 0x1);

	TEST_END();
}

void test_and_indx(CPU cpu, MEMORY memory)
{

	int number_of_instructions;

	TEST_START("AND Indirect X - MATCH");

	cpu_reset(&cpu, &memory);

	cpu.a = 0x15;
	cpu.x = 0x04;
	memory.data[0xFFFC] = INS_AND_INDX;
	memory.data[0xFFFD] = 0x02;
	memory.data[0x0006] = 0x00;
	memory.data[0x0007] = 0x80;
	memory.data[0x8000] = 0x15;

	number_of_instructions = instruction_execute(&cpu, &memory);

	EXPECT_EQ(number_of_instructions, 6);
	EXPECT_EQ(cpu.a, 0x15);

	TEST_END();

	TEST_START("AND Indirect X - NOT A MATCH");

	cpu_reset(&cpu, &memory);

	cpu.a = 0x5;
	cpu.x = 0x04;
	memory.data[0xFFFC] = INS_AND_INDX;
	memory.data[0xFFFD] = 0x02;
	memory.data[0x0006] = 0x00;
	memory.data[0x0007] = 0x80;
	memory.data[0x8000] = 0x3;

	number_of_instructions = instruction_execute(&cpu, &memory);

	EXPECT_EQ(number_of_instructions, 6);
	EXPECT_EQ(cpu.a, 0x1);

	TEST_END();

	TEST_START("AND Indirect X - NO EQUAL BITS");

	cpu_reset(&cpu, &memory);

	cpu.a = 0x3;
	cpu.x = 0x04;
	memory.data[0xFFFC] = INS_AND_INDX;
	memory.data[0xFFFD] = 0x02;
	memory.data[0x0006] = 0x00;
	memory.data[0x0007] = 0x80;
	memory.data[0x8000] = 0x0;

	number_of_instructions = instruction_execute(&cpu, &memory);

	EXPECT_EQ(number_of_instructions, 6);
	EXPECT_EQ(cpu.a, 0x0);

	TEST_END();
}

void test_and_indy(CPU cpu, MEMORY memory)
{
	int number_of_instructions;

	TEST_START("AND INDY - MATCH");

	cpu_reset(&cpu, &memory);

	cpu.y = 0x04;
	cpu.a = 0x15;
	memory.data[0xFFFC] = INS_AND_INDY;
	memory.data[0xFFFD] = 0x02;
	memory.data[0x0002] = 0x00;
	memory.data[0x0003] = 0x80;
	memory.data[0x8004] = 0x15;

	number_of_instructions = instruction_execute(&cpu, &memory);

	EXPECT_EQ(number_of_instructions, 5);
	EXPECT_EQ(cpu.a, 0x15);

	TEST_END();

	TEST_START("AND INDY - NOT A MATCH");

	cpu_reset(&cpu, &memory);

	cpu.y = 0x04;
	cpu.a = 0x3;
	memory.data[0xFFFC] = INS_AND_INDY;
	memory.data[0xFFFD] = 0x02;
	memory.data[0x0002] = 0x00;
	memory.data[0x0003] = 0x80;
	memory.data[0x8004] = 0x5;

	number_of_instructions = instruction_execute(&cpu, &memory);

	EXPECT_EQ(number_of_instructions, 5);
	EXPECT_EQ(cpu.a, 0x1);

	TEST_END();

	TEST_START("AND INDY - NO EQUAL BITS");

	cpu_reset(&cpu, &memory);

	cpu.y = 0x04;
	cpu.a = 0x5;
	memory.data[0xFFFC] = INS_AND_INDY;
	memory.data[0xFFFD] = 0x02;
	memory.data[0x0002] = 0x00;
	memory.data[0x0003] = 0x80;
	memory.data[0x8004] = 0x0;

	number_of_instructions = instruction_execute(&cpu, &memory);

	EXPECT_EQ(number_of_instructions, 5);
	EXPECT_EQ(cpu.a, 0x0);

	TEST_END();

	TEST_START("AND INDY - PAGE CROSSED");

	cpu_reset(&cpu, &memory);

	cpu.y = 0x04;
	cpu.a = 0x5;
	memory.data[0xFFFC] = INS_AND_INDY;
	memory.data[0xFFFD] = 0x02;
	memory.data[0x0002] = 0xFF;
	memory.data[0x0003] = 0x00;
	memory.data[0x00FF + cpu.y] = 0x0;

	number_of_instructions = instruction_execute(&cpu, &memory);

	EXPECT_EQ(number_of_instructions, 6);
	EXPECT_EQ(cpu.a, 0x0);

	TEST_END();
}

void test_eor_im(CPU cpu, MEMORY memory)
{
	int number_of_instructions;

	TEST_START("EOR IMMEDIATE - EQUAL NUMBERS");

	cpu_reset(&cpu, &memory);

	cpu.a = 0x15;
	memory.data[0xFFFC] = INS_EOR_IM;
	memory.data[0xFFFD] = 0x15;

	number_of_instructions = instruction_execute(&cpu, &memory);

	EXPECT_EQ(number_of_instructions, 2);
	EXPECT_EQ(cpu.a, 0x0);

	TEST_END();

	TEST_START("EOR IMMEDIATE - 1 BIT MATCH");

	cpu_reset(&cpu, &memory);

	cpu.a = 0x1;
	memory.data[0xFFFC] = INS_EOR_IM;
	memory.data[0xFFFD] = 0x0;

	number_of_instructions = instruction_execute(&cpu, &memory);

	EXPECT_EQ(number_of_instructions, 2);
	EXPECT_EQ(cpu.a, 0x1);

	TEST_END();

	TEST_START("EOR IMMEDIATE - NO MATCH");

	cpu_reset(&cpu, &memory);

	cpu.a = 85;
	memory.data[0xFFFC] = INS_EOR_IM;
	memory.data[0xFFFD] = 42;

	number_of_instructions = instruction_execute(&cpu, &memory);

	EXPECT_EQ(number_of_instructions, 2);
	EXPECT_EQ(cpu.a, 127);

	TEST_END();
}

void test_eor_zp(CPU cpu, MEMORY memory)
{
	int number_of_instructions;

	TEST_START("EOR ZERO PAGE - EQUAL NUMBERS");

	cpu_reset(&cpu, &memory);

	cpu.a = 0x15;
	memory.data[0xFFFC] = INS_EOR_ZP;
	memory.data[0xFFFD] = 0x15;
	memory.data[0x0015] = 0x15;

	number_of_instructions = instruction_execute(&cpu, &memory);

	EXPECT_EQ(number_of_instructions, 3);
	EXPECT_EQ(cpu.a, 0x0);

	TEST_END();

	TEST_START("EOR ZERO PAGE - 1 BIT MATCH");

	cpu_reset(&cpu, &memory);

	cpu.a = 0x1;
	memory.data[0xFFFC] = INS_EOR_ZP;
	memory.data[0xFFFD] = 0x15;
	memory.data[0x0015] = 0x0;

	number_of_instructions = instruction_execute(&cpu, &memory);

	EXPECT_EQ(number_of_instructions, 3);
	EXPECT_EQ(cpu.a, 0x1);

	TEST_END();

	TEST_START("EOR ZERO PAGE - NO MATCH");

	cpu_reset(&cpu, &memory);

	cpu.a = 85;
	memory.data[0xFFFC] = INS_EOR_ZP;
	memory.data[0xFFFD] = 0x15;
	memory.data[0x0015] = 42;

	number_of_instructions = instruction_execute(&cpu, &memory);

	EXPECT_EQ(number_of_instructions, 3);
	EXPECT_EQ(cpu.a, 127);

	TEST_END();
}

void test_eor_zpx(CPU cpu, MEMORY memory)
{
	int number_of_instructions;

	TEST_START("EOR ZERO PAGE X - EQUAL NUMBERS");

	cpu_reset(&cpu, &memory);

	cpu.a = 0x15;
	cpu.x = 0x13;
	memory.data[0xFFFC] = INS_EOR_ZPX;
	memory.data[0xFFFD] = 0x15;
	memory.data[0x0015 + cpu.x] = 0x15;

	number_of_instructions = instruction_execute(&cpu, &memory);

	EXPECT_EQ(number_of_instructions, 4);
	EXPECT_EQ(cpu.a, 0x0);

	TEST_END();

	TEST_START("EOR ZERO PAGE X - 1 BIT MATCH");

	cpu_reset(&cpu, &memory);

	cpu.a = 0x1;
	cpu.x = 0x13;
	memory.data[0xFFFC] = INS_EOR_ZPX;
	memory.data[0xFFFD] = 0x15;
	memory.data[0x0015 + cpu.x] = 0x0;

	number_of_instructions = instruction_execute(&cpu, &memory);

	EXPECT_EQ(number_of_instructions, 4);
	EXPECT_EQ(cpu.a, 0x1);

	TEST_END();

	TEST_START("EOR ZERO PAGE X - NO MATCH");

	cpu_reset(&cpu, &memory);

	cpu.a = 85;
	cpu.x = 0x13;
	memory.data[0xFFFC] = INS_EOR_ZPX;
	memory.data[0xFFFD] = 0x15;
	memory.data[0x0015 + cpu.x] = 42;

	number_of_instructions = instruction_execute(&cpu, &memory);

	EXPECT_EQ(number_of_instructions, 4);
	EXPECT_EQ(cpu.a, 127);

	TEST_END();
}

void test_eor_abs(CPU cpu, MEMORY memory)
{
	int number_of_instructions;

	TEST_START("EOR ABSOLUTE - EQUAL NUMBERS");

	cpu_reset(&cpu, &memory);

	cpu.a = 0x15;
	memory.data[0xFFFC] = INS_EOR_ABS;
	memory.data[0xFFFD] = 0x12;
	memory.data[0xFFFE] = 0x34;
	memory.data[0x3412] = 0x15;

	number_of_instructions = instruction_execute(&cpu, &memory);

	EXPECT_EQ(number_of_instructions, 4);
	EXPECT_EQ(cpu.a, 0x0);

	TEST_END();

	TEST_START("EOR ABSOLUTE - 1 BIT MATCH");

	cpu_reset(&cpu, &memory);

	cpu.a = 0x1;
	memory.data[0xFFFC] = INS_EOR_ABS;
	memory.data[0xFFFD] = 0x12;
	memory.data[0xFFFE] = 0x34;
	memory.data[0x3412] = 0x0;

	number_of_instructions = instruction_execute(&cpu, &memory);

	EXPECT_EQ(number_of_instructions, 4);
	EXPECT_EQ(cpu.a, 0x1);

	TEST_END();

	TEST_START("EOR ABSOLUTE - NO MATCH");

	cpu_reset(&cpu, &memory);

	cpu.a = 85;
	memory.data[0xFFFC] = INS_EOR_ABS;
	memory.data[0xFFFD] = 0x12;
	memory.data[0xFFFE] = 0x34;
	memory.data[0x3412] = 42;

	number_of_instructions = instruction_execute(&cpu, &memory);

	EXPECT_EQ(number_of_instructions, 4);
	EXPECT_EQ(cpu.a, 127);

	TEST_END();
}

void test_eor_absx(CPU cpu, MEMORY memory)
{
	int number_of_instructions;

	TEST_START("EOR ABSOLUTE X - EQUAL NUMBERS");

	cpu_reset(&cpu, &memory);

	cpu.a = 0x15;
	cpu.x = 0x15;
	memory.data[0xFFFC] = INS_EOR_ABSX;
	memory.data[0xFFFD] = 0x12;
	memory.data[0xFFFE] = 0x34;
	memory.data[0x3412 + cpu.x] = 0x15;

	number_of_instructions = instruction_execute(&cpu, &memory);

	EXPECT_EQ(number_of_instructions, 4);
	EXPECT_EQ(cpu.a, 0x0);

	TEST_END();

	TEST_START("EOR ABSOLUTE X - 1 BIT MATCH");

	cpu_reset(&cpu, &memory);

	cpu.a = 0x1;
	cpu.x = 0x15;
	memory.data[0xFFFC] = INS_EOR_ABSX;
	memory.data[0xFFFD] = 0x12;
	memory.data[0xFFFE] = 0x34;
	memory.data[0x3412 + cpu.x] = 0x0;

	number_of_instructions = instruction_execute(&cpu, &memory);

	EXPECT_EQ(number_of_instructions, 4);
	EXPECT_EQ(cpu.a, 0x1);

	TEST_END();

	TEST_START("EOR ABSOLUTE X - NO MATCH");

	cpu_reset(&cpu, &memory);

	cpu.a = 85;
	cpu.x = 0x15;
	memory.data[0xFFFC] = INS_EOR_ABSX;
	memory.data[0xFFFD] = 0x12;
	memory.data[0xFFFE] = 0x34;
	memory.data[0x3412 + cpu.x] = 42;

	number_of_instructions = instruction_execute(&cpu, &memory);

	EXPECT_EQ(number_of_instructions, 4);
	EXPECT_EQ(cpu.a, 127);

	TEST_END();
	TEST_START("EOR ABSOLUTE X - PAGE CROSSED");

	cpu_reset(&cpu, &memory);

	cpu.a = 85;
	cpu.x = 0x15;
	memory.data[0xFFFC] = INS_EOR_ABSX;
	memory.data[0xFFFD] = 0xFF;
	memory.data[0xFFFE] = 0x00;
	memory.data[0x00FF + cpu.x] = 42;

	number_of_instructions = instruction_execute(&cpu, &memory);

	EXPECT_EQ(number_of_instructions, 5);
	EXPECT_EQ(cpu.a, 127);

	TEST_END();
}

void test_eor_absy(CPU cpu, MEMORY memory)
{
	int number_of_instructions;

	TEST_START("EOR ABSOLUTE Y - EQUAL NUMBERS");

	cpu_reset(&cpu, &memory);

	cpu.a = 0x15;
	cpu.y = 0x15;
	memory.data[0xFFFC] = INS_EOR_ABSY;
	memory.data[0xFFFD] = 0x12;
	memory.data[0xFFFE] = 0x34;
	memory.data[0x3412 + cpu.y] = 0x15;

	number_of_instructions = instruction_execute(&cpu, &memory);

	EXPECT_EQ(number_of_instructions, 4);
	EXPECT_EQ(cpu.a, 0x0);

	TEST_END();

	TEST_START("EOR ABSOLUTE Y - 1 BIT MATCH");

	cpu_reset(&cpu, &memory);

	cpu.a = 0x1;
	cpu.y = 0x15;
	memory.data[0xFFFC] = INS_EOR_ABSY;
	memory.data[0xFFFD] = 0x12;
	memory.data[0xFFFE] = 0x34;
	memory.data[0x3412 + cpu.y] = 0x0;

	number_of_instructions = instruction_execute(&cpu, &memory);

	EXPECT_EQ(number_of_instructions, 4);
	EXPECT_EQ(cpu.a, 0x1);

	TEST_END();

	TEST_START("EOR ABSOLUTE Y - NO MATCH");

	cpu_reset(&cpu, &memory);

	cpu.a = 85;
	cpu.y = 0x15;
	memory.data[0xFFFC] = INS_EOR_ABSY;
	memory.data[0xFFFD] = 0x12;
	memory.data[0xFFFE] = 0x34;
	memory.data[0x3412 + cpu.y] = 42;

	number_of_instructions = instruction_execute(&cpu, &memory);

	EXPECT_EQ(number_of_instructions, 4);
	EXPECT_EQ(cpu.a, 127);

	TEST_END();
	TEST_START("EOR ABSOLUTE Y - PAGE CROSSED");

	cpu_reset(&cpu, &memory);

	cpu.a = 85;
	cpu.y = 0x15;
	memory.data[0xFFFC] = INS_EOR_ABSY;
	memory.data[0xFFFD] = 0xFF;
	memory.data[0xFFFE] = 0x00;
	memory.data[0x00FF + cpu.y] = 42;

	number_of_instructions = instruction_execute(&cpu, &memory);

	EXPECT_EQ(number_of_instructions, 5);
	EXPECT_EQ(cpu.a, 127);

	TEST_END();
}

void test_eor_indx(CPU cpu, MEMORY memory)
{

	int number_of_instructions;

	TEST_START("EOR Indirect X - EQUAL NUMBERS");

	cpu_reset(&cpu, &memory);

	cpu.a = 0x15;
	cpu.x = 0x04;
	memory.data[0xFFFC] = INS_EOR_INDX;
	memory.data[0xFFFD] = 0x02;
	memory.data[0x0006] = 0x00;
	memory.data[0x0007] = 0x80;
	memory.data[0x8000] = 0x15;

	number_of_instructions = instruction_execute(&cpu, &memory);

	EXPECT_EQ(number_of_instructions, 6);
	EXPECT_EQ(cpu.a, 0x0);

	TEST_END();

	TEST_START("EOR Indirect X - 1 BIT MATCH");

	cpu_reset(&cpu, &memory);

	cpu.a = 0x1;
	cpu.x = 0x04;
	memory.data[0xFFFC] = INS_EOR_INDX;
	memory.data[0xFFFD] = 0x02;
	memory.data[0x0006] = 0x00;
	memory.data[0x0007] = 0x80;
	memory.data[0x8000] = 0x0;

	number_of_instructions = instruction_execute(&cpu, &memory);

	EXPECT_EQ(number_of_instructions, 6);
	EXPECT_EQ(cpu.a, 0x1);

	TEST_END();

	TEST_START("EOR Indirect X - NO MATCH");

	cpu_reset(&cpu, &memory);

	cpu.a = 85;
	cpu.x = 0x04;
	memory.data[0xFFFC] = INS_EOR_INDX;
	memory.data[0xFFFD] = 0x02;
	memory.data[0x0006] = 0x00;
	memory.data[0x0007] = 0x80;
	memory.data[0x8000] = 42;

	number_of_instructions = instruction_execute(&cpu, &memory);

	EXPECT_EQ(number_of_instructions, 6);
	EXPECT_EQ(cpu.a, 127);

	TEST_END();
}

void test_eor_indy(CPU cpu, MEMORY memory)
{
	int number_of_instructions;

	TEST_START("EOR INDY - EQUAL NUMBERS");

	cpu_reset(&cpu, &memory);

	cpu.y = 0x04;
	cpu.a = 0x15;
	memory.data[0xFFFC] = INS_EOR_INDY;
	memory.data[0xFFFD] = 0x02;
	memory.data[0x0002] = 0x00;
	memory.data[0x0003] = 0x80;
	memory.data[0x8004] = 0x15;

	number_of_instructions = instruction_execute(&cpu, &memory);

	EXPECT_EQ(number_of_instructions, 5);
	EXPECT_EQ(cpu.a, 0x0);

	TEST_END();

	TEST_START("EOR INDY - 1 BIT MATCH");

	cpu_reset(&cpu, &memory);

	cpu.y = 0x04;
	cpu.a = 0x1;
	memory.data[0xFFFC] = INS_EOR_INDY;
	memory.data[0xFFFD] = 0x02;
	memory.data[0x0002] = 0x00;
	memory.data[0x0003] = 0x80;
	memory.data[0x8004] = 0x0;

	number_of_instructions = instruction_execute(&cpu, &memory);

	EXPECT_EQ(number_of_instructions, 5);
	EXPECT_EQ(cpu.a, 0x1);

	TEST_END();

	TEST_START("EOR INDY - NO MATCH");

	cpu_reset(&cpu, &memory);

	cpu.y = 0x04;
	cpu.a = 85;
	memory.data[0xFFFC] = INS_EOR_INDY;
	memory.data[0xFFFD] = 0x02;
	memory.data[0x0002] = 0x00;
	memory.data[0x0003] = 0x80;
	memory.data[0x8004] = 42;

	number_of_instructions = instruction_execute(&cpu, &memory);

	EXPECT_EQ(number_of_instructions, 5);
	EXPECT_EQ(cpu.a, 127);

	TEST_END();

	TEST_START("EOR INDY - PAGE CROSSED");

	cpu_reset(&cpu, &memory);

	cpu.y = 0x04;
	cpu.a = 85;
	memory.data[0xFFFC] = INS_EOR_INDY;
	memory.data[0xFFFD] = 0x02;
	memory.data[0x0002] = 0xFF;
	memory.data[0x0003] = 0x00;
	memory.data[0x00FF + cpu.y] = 42;

	number_of_instructions = instruction_execute(&cpu, &memory);

	EXPECT_EQ(number_of_instructions, 6);
	EXPECT_EQ(cpu.a, 127);

	TEST_END();
}

void test_ora_im(CPU cpu, MEMORY memory)
{
	int number_of_instructions;

	TEST_START("ORA IMMEDIATE - EQUAL NUMBERS");

	cpu_reset(&cpu, &memory);

	cpu.a = 0x15;
	memory.data[0xFFFC] = INS_ORA_IM;
	memory.data[0xFFFD] = 0x15;

	number_of_instructions = instruction_execute(&cpu, &memory);

	EXPECT_EQ(number_of_instructions, 2);
	EXPECT_EQ(cpu.a, 0x15);

	TEST_END();

	TEST_START("ORA IMMEDIATE - 1 BIT MATCH");

	cpu_reset(&cpu, &memory);

	cpu.a = 0x1;
	memory.data[0xFFFC] = INS_ORA_IM;
	memory.data[0xFFFD] = 0x0;

	number_of_instructions = instruction_execute(&cpu, &memory);

	EXPECT_EQ(number_of_instructions, 2);
	EXPECT_EQ(cpu.a, 0x1);

	TEST_END();

	TEST_START("ORA IMMEDIATE - NO MATCH");

	cpu_reset(&cpu, &memory);

	cpu.a = 85;
	memory.data[0xFFFC] = INS_ORA_IM;
	memory.data[0xFFFD] = 42;

	number_of_instructions = instruction_execute(&cpu, &memory);

	EXPECT_EQ(number_of_instructions, 2);
	EXPECT_EQ(cpu.a, 127);

	TEST_END();
}

void test_ora_zp(CPU cpu, MEMORY memory)
{
	int number_of_instructions;

	TEST_START("ORA ZP - EQUAL NUMBERS");

	cpu_reset(&cpu, &memory);

	cpu.a = 0x15;
	memory.data[0xFFFC] = INS_ORA_ZP;
	memory.data[0xFFFD] = 0x42;
	memory.data[0x0042] = 0x15;

	number_of_instructions = instruction_execute(&cpu, &memory);

	EXPECT_EQ(number_of_instructions, 3);
	EXPECT_EQ(cpu.a, 0x15);

	TEST_END();

	TEST_START("ORA ZP - 1 BIT MATCH");

	cpu_reset(&cpu, &memory);

	cpu.a = 0x1;
	memory.data[0xFFFC] = INS_ORA_ZP;
	memory.data[0xFFFD] = 0x42;
	memory.data[0x0042] = 0x0;

	number_of_instructions = instruction_execute(&cpu, &memory);

	EXPECT_EQ(number_of_instructions, 3);
	EXPECT_EQ(cpu.a, 0x1);

	TEST_END();

	TEST_START("ORA ZP - NO MATCH");

	cpu_reset(&cpu, &memory);

	cpu.a = 85;
	memory.data[0xFFFC] = INS_ORA_ZP;
	memory.data[0xFFFD] = 0x42;
	memory.data[0x0042] = 42;

	number_of_instructions = instruction_execute(&cpu, &memory);

	EXPECT_EQ(number_of_instructions, 3);
	EXPECT_EQ(cpu.a, 127);

	TEST_END();
}

void test_ora_zpx(CPU cpu, MEMORY memory)
{
	int number_of_instructions;

	TEST_START("ORA ZERO PAGE X - EQUAL NUMBERS");

	cpu_reset(&cpu, &memory);

	cpu.a = 0x15;
	cpu.x = 0x13;
	memory.data[0xFFFC] = INS_ORA_ZPX;
	memory.data[0xFFFD] = 0x15;
	memory.data[0x0015 + cpu.x] = 0x15;

	number_of_instructions = instruction_execute(&cpu, &memory);

	EXPECT_EQ(number_of_instructions, 4);
	EXPECT_EQ(cpu.a, 0x15);

	TEST_END();

	TEST_START("ORA ZERO PAGE X - 1 BIT MATCH");

	cpu_reset(&cpu, &memory);

	cpu.a = 0x1;
	cpu.x = 0x13;
	memory.data[0xFFFC] = INS_ORA_ZPX;
	memory.data[0xFFFD] = 0x15;
	memory.data[0x0015 + cpu.x] = 0x0;

	number_of_instructions = instruction_execute(&cpu, &memory);

	EXPECT_EQ(number_of_instructions, 4);
	EXPECT_EQ(cpu.a, 0x1);

	TEST_END();

	TEST_START("ORA ZERO PAGE X - NO MATCH");

	cpu_reset(&cpu, &memory);

	cpu.a = 85;
	cpu.x = 0x13;
	memory.data[0xFFFC] = INS_ORA_ZPX;
	memory.data[0xFFFD] = 0x15;
	memory.data[0x0015 + cpu.x] = 42;

	number_of_instructions = instruction_execute(&cpu, &memory);

	EXPECT_EQ(number_of_instructions, 4);
	EXPECT_EQ(cpu.a, 127);

	TEST_END();
}

void test_ora_abs(CPU cpu, MEMORY memory)
{
	int number_of_instructions;

	TEST_START("ORA ABSOLUTE - EQUAL NUMBERS");

	cpu_reset(&cpu, &memory);

	cpu.a = 0x15;
	memory.data[0xFFFC] = INS_ORA_ABS;
	memory.data[0xFFFD] = 0x12;
	memory.data[0xFFFE] = 0x34;
	memory.data[0x3412] = 0x15;

	number_of_instructions = instruction_execute(&cpu, &memory);

	EXPECT_EQ(number_of_instructions, 4);
	EXPECT_EQ(cpu.a, 0x15);

	TEST_END();

	TEST_START("ORA ABSOLUTE - 1 BIT MATCH");

	cpu_reset(&cpu, &memory);

	cpu.a = 0x1;
	memory.data[0xFFFC] = INS_ORA_ABS;
	memory.data[0xFFFD] = 0x12;
	memory.data[0xFFFE] = 0x34;
	memory.data[0x3412] = 0x0;

	number_of_instructions = instruction_execute(&cpu, &memory);

	EXPECT_EQ(number_of_instructions, 4);
	EXPECT_EQ(cpu.a, 0x1);

	TEST_END();

	TEST_START("ORA ABSOLUTE - NO MATCH");

	cpu_reset(&cpu, &memory);

	cpu.a = 85;
	memory.data[0xFFFC] = INS_ORA_ABS;
	memory.data[0xFFFD] = 0x12;
	memory.data[0xFFFE] = 0x34;
	memory.data[0x3412] = 42;

	number_of_instructions = instruction_execute(&cpu, &memory);

	EXPECT_EQ(number_of_instructions, 4);
	EXPECT_EQ(cpu.a, 127);

	TEST_END();
}

void test_ora_absx(CPU cpu, MEMORY memory)
{
	int number_of_instructions;

	TEST_START("ORA ABSOLUTE X - EQUAL NUMBERS");

	cpu_reset(&cpu, &memory);

	cpu.a = 0x15;
	cpu.x = 0x15;
	memory.data[0xFFFC] = INS_ORA_ABSX;
	memory.data[0xFFFD] = 0x12;
	memory.data[0xFFFE] = 0x34;
	memory.data[0x3412 + cpu.x] = 0x15;

	number_of_instructions = instruction_execute(&cpu, &memory);

	EXPECT_EQ(number_of_instructions, 4);
	EXPECT_EQ(cpu.a, 0x15);

	TEST_END();

	TEST_START("ORA ABSOLUTE X - 1 BIT MATCH");

	cpu_reset(&cpu, &memory);

	cpu.a = 0x1;
	cpu.x = 0x15;
	memory.data[0xFFFC] = INS_ORA_ABSX;
	memory.data[0xFFFD] = 0x12;
	memory.data[0xFFFE] = 0x34;
	memory.data[0x3412 + cpu.x] = 0x0;

	number_of_instructions = instruction_execute(&cpu, &memory);

	EXPECT_EQ(number_of_instructions, 4);
	EXPECT_EQ(cpu.a, 0x1);

	TEST_END();

	TEST_START("ORA ABSOLUTE X - NO MATCH");

	cpu_reset(&cpu, &memory);

	cpu.a = 85;
	cpu.x = 0x15;
	memory.data[0xFFFC] = INS_ORA_ABSX;
	memory.data[0xFFFD] = 0x12;
	memory.data[0xFFFE] = 0x34;
	memory.data[0x3412 + cpu.x] = 42;

	number_of_instructions = instruction_execute(&cpu, &memory);

	EXPECT_EQ(number_of_instructions, 4);
	EXPECT_EQ(cpu.a, 127);

	TEST_END();
	TEST_START("ORA ABSOLUTE X - PAGE CROSSED");

	cpu_reset(&cpu, &memory);

	cpu.a = 85;
	cpu.x = 0x15;
	memory.data[0xFFFC] = INS_ORA_ABSX;
	memory.data[0xFFFD] = 0xFF;
	memory.data[0xFFFE] = 0x00;
	memory.data[0x00FF + cpu.x] = 42;

	number_of_instructions = instruction_execute(&cpu, &memory);

	EXPECT_EQ(number_of_instructions, 5);
	EXPECT_EQ(cpu.a, 127);

	TEST_END();
}
