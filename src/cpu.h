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
	WORD pc;
	BYTE sp;

	// Registers
	BYTE a;
	BYTE x;
	BYTE y;

	// Stauts flags
	BYTE c : 1; // Carry
	BYTE z : 1; // Zero
	BYTE i : 1; // Interrupt
	BYTE d : 1; // Decimal mode
	BYTE b : 1; // Break
	BYTE v : 1; // Overflow
	BYTE n : 1; // Negative
} CPU;

// Opcodes
#define INS_LDA_IM 0xA9
#define INS_LDA_ZP 0xA5
#define INS_LDA_ZPX 0xB5
#define INS_LDA_ABS 0xAD
#define INS_LDA_ABSX 0xBD
#define INS_LDA_ABSY 0xB9
// Indexed-indirect
#define INS_LDA_INDX 0xA1
// Indirect-indexed
#define INS_LDA_INDY 0xB1

#define INS_LDX_IM 0xA2
#define INS_LDX_ZP 0xA6
#define INS_LDX_ZPY 0xB6
#define INS_LDX_IM 0xA2
#define INS_LDX_ABS 0xAE
#define INS_LDX_ABSY 0xBE

#define INS_LDY_IM 0xA0
#define INS_LDY_ZP 0xA4
#define INS_LDY_ZPX 0xB4
#define INS_LDY_ABS 0xAC
#define INS_LDY_ABSX 0xBC

#define INS_STA_ZP 0x85
#define INS_STA_ZPX 0x95
#define INS_STA_ABS 0x8D
#define INS_STA_ABSX 0x9D
#define INS_STA_ABSY 0x99
#define INS_STA_INDX 0x81
#define INS_STA_INDY 0x91

#define INS_JSR 0x20

// Functions
void reset_cpu(CPU *cpu, MEMORY *memory);
void initialise_memory(MEMORY *memory);
int execute_instruction(CPU *cpu, MEMORY *memory);
BYTE fetch_byte(int *clock, CPU *cpu, MEMORY *memory);
BYTE read_byte(int *clock, WORD address, MEMORY *memory);
void write_byte(int *clock, WORD address, BYTE value, CPU *cpu, MEMORY *memory);
WORD fetch_word(int *clock, CPU *cpu, MEMORY *memory);
WORD read_word(int *clock, WORD address, MEMORY *memory);
void write_word(int *clock, WORD address, WORD value, MEMORY *memory);
void load_set_flags(CPU *cpu, BYTE register_data);
void print_memory(MEMORY *memory, int start, int end);

#endif // CPU_H_
