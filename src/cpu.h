/*
	 MIT License

	 Copyright (c) [2022] [author]

	 Permission is hereby granted, free of charge, to any person obtaining a copy
	 of this software and associated documentation files (the "Software"), to deal
	 in the Software without restriction, including without limitation the rights
	 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
	 copies of the Software, and to permit persons to whom the Software is
	 furnished to do so, subject to the following conditions:

	 The above copyright notice and this permission notice shall be included in all
	 copies or substantial portions of the Software.

	 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
	 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
	 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
	 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
	 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
	 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
	 SOFTWARE.
*/

#ifndef CPU_H_
#define CPU_H_

#include <stdio.h>
#include <math.h>
#include <string.h>
#include <assert.h>
#include <stdint.h>
#include <stdbool.h>

#define STACK_OFFSET 0x0100

// 2^16 = 16K
#define MEMORY_SIZE 1024 * 64


typedef uint8_t BYTE;
typedef uint16_t WORD;


typedef struct
{
	BYTE data[MEMORY_SIZE];
} MEMORY;


typedef struct
{
	WORD pc; // Program counter
	BYTE sp; // Stack pointer

	/* Registers */
	BYTE a;
	BYTE x;
	BYTE y;

	/* Status flags */
	BYTE c : 1; // Carry
	BYTE z : 1; // Zero
	BYTE i : 1; // Interrupt
	BYTE d : 1; // Decimal mode
	BYTE b : 1; // Break
	BYTE v : 1; // Overflow
	BYTE n : 1; // Negative
} CPU;


/* Opcodes */
/* Load instructions */
/* LDA */
#define INS_LDA_IM		0xA9
#define INS_LDA_ZP		0xA5
#define INS_LDA_ZPX		0xB5
#define INS_LDA_ABS		0xAD
#define INS_LDA_ABSX	0xBD
#define INS_LDA_ABSY	0xB9
#define INS_LDA_INDX	0xA1 // Indexed-indirect
#define INS_LDA_INDY	0xB1 // Indirect-indexed

/* LDX*/
#define INS_LDX_IM		0xA2
#define INS_LDX_ZP		0xA6
#define INS_LDX_ZPY		0xB6
#define INS_LDX_IM		0xA2
#define INS_LDX_ABS		0xAE
#define INS_LDX_ABSY	0xBE

/* LDY */
#define INS_LDY_IM		0xA0
#define INS_LDY_ZP		0xA4
#define INS_LDY_ZPX		0xB4
#define INS_LDY_ABS		0xAC
#define INS_LDY_ABSX	0xBC

/* Store instructions */
/* STA */
#define INS_STA_ZP		0x85
#define INS_STA_ZPX		0x95
#define INS_STA_ABS		0x8D
#define INS_STA_ABSX	0x9D
#define INS_STA_ABSY	0x99
#define INS_STA_INDX	0x81 // Indexed-indirect
#define INS_STA_INDY	0x91 // Indirect-indexed

/* STX */
#define INS_STX_ZP		0x86
#define INS_STX_ZPY		0x96
#define INS_STX_ABS		0x8E

/* STY */
#define INS_STY_ZP		0x84
#define INS_STY_ZPX		0x94
#define INS_STY_ABS		0x8C

/* Transfer instructions */
#define INS_TAX			0xAA
#define INS_TAY			0xA8
#define INS_TXA			0x8A
#define INS_TYA			0x98
#define INS_TSX			0xBA
#define INS_TXS			0x9A

/* Stack instructions */
#define INS_PHA			0x48
#define INS_PLA			0x68
#define INS_PHP			0x08
#define INS_PLP			0x28

/* Logical operations */
/* AND */
#define INS_AND_IM		0x29
#define INS_AND_ZP		0x25
#define INS_AND_ZPX		0x35
#define INS_AND_ABS		0x2D
#define INS_AND_ABSX	0x3D
#define INS_AND_ABSY	0x39
#define INS_AND_INDX	0x21
#define INS_AND_INDY	0x31

/* EOR */
#define INS_EOR_IM		0x49
#define INS_EOR_ZP		0x45
#define INS_EOR_ZPX		0x55
#define INS_EOR_ABS		0x4D
#define INS_EOR_ABSX	0x5D
#define INS_EOR_ABSY	0x59
#define INS_EOR_INDX	0x41
#define INS_EOR_INDY	0x51

/* ORA */
#define INS_ORA_IM		0x09
#define INS_ORA_ZP		0x05
#define INS_ORA_ZPX		0x15
#define INS_ORA_ABS		0x0D
#define INS_ORA_ABSX	0x1D

#define INS_JSR			0x20


/* Functions */
/* CPU */
void cpu_reset(CPU *cpu, MEMORY *memory);
void cpu_ld_set_flags(CPU *cpu, BYTE register_data);

/* Memory */
void memory_initialize(MEMORY *memory);
void memory_print(MEMORY *memory, int start, int end);

int instruction_execute(CPU *cpu, MEMORY *memory);

/* Byte */
BYTE byte_fetch(int *clock, CPU *cpu, MEMORY *memory);
BYTE byte_read(int *clock, WORD address, MEMORY *memory);
BYTE byte_pop(int *clock, CPU *cpu, MEMORY *memory);
void byte_write(int *clock, WORD address, BYTE value, CPU *cpu, MEMORY *memory);
void byte_push(int *clock, BYTE data, CPU *cpu, MEMORY *memory);

/* Word */
WORD word_fetch(int *clock, CPU *cpu, MEMORY *memory);
WORD word_read(int *clock, WORD address, MEMORY *memory);
void word_write(int *clock, WORD address, WORD value, MEMORY *memory);

#endif // CPU_H_
