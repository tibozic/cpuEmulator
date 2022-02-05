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

/* TAX */
#define INS_TAX			0xAA
/* TAY */
#define INS_TAY			0xA8
/* TXA */
#define INS_TXA			0x8A
/* TXA */
#define INS_TYA			0x98
/* TSX */
#define INS_TSX			0xBA
/* TXS */
#define INS_TXS			0x9A

#define INS_JSR			0x20



/* Functions */
/* CPU */
void cpu_reset(CPU *cpu, MEMORY *memory);
void cpu_ld_set_flags(CPU *cpu, BYTE register_data);

/* Memory */
void memory_initialise(MEMORY *memory);
void memory_print(MEMORY *memory, int start, int end);

int instruction_execute(CPU *cpu, MEMORY *memory);

/* Byte */
BYTE byte_fetch(int *clock, CPU *cpu, MEMORY *memory);
BYTE byte_read(int *clock, WORD address, MEMORY *memory);
void byte_write(int *clock, WORD address, BYTE value, CPU *cpu, MEMORY *memory);

/* Word */
WORD word_fetch(int *clock, CPU *cpu, MEMORY *memory);
WORD word_read(int *clock, WORD address, MEMORY *memory);
void word_write(int *clock, WORD address, WORD value, MEMORY *memory);

#endif // CPU_H_
