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

	// kk
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
#define INS_STA_ZP 0x85
#define INS_LDX_IM 0xA2
#define INS_LDX_ZP 0xA6
#define INS_LDX_ZPX 0xB6
#define INS_LDX_ABS 0xAE
#define INS_JSR 0x20

// Functions
void reset_cpu(CPU *cpu, MEMORY *memory);
void initialise_memory(MEMORY *memory);
int execute_instruction(CPU *cpu, MEMORY *memory);
BYTE fetch_byte(int *clock, CPU *cpu, MEMORY *memory);
BYTE read_byte(int *clock, BYTE address, MEMORY *memory);
void write_byte(int *clock, BYTE address, BYTE value, CPU *cpu, MEMORY *memory);
WORD fetch_word(int *clock, CPU *cpu, MEMORY *memory);
void write_word(int *clock, WORD address, WORD value, MEMORY *memory);
void load_set_flags(CPU *cpu, BYTE register_data);
void print_memory(MEMORY *memory, int start, int end);
BYTE read_word(int *clock, WORD address, MEMORY *memory);

#endif // CPU_H_
