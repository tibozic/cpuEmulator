#include <stdio.h>
#include <math.h>
#include <string.h>
#include <assert.h>

#define STACK_OFFSET 0x0100

// 2^16 = 16K
#define MEMORY_SIZE 1024 * 64

typedef unsigned char BYTE;
typedef unsigned short WORD;

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
#define END 0x0

// Functions
void reset_cpu(CPU *cpu, MEMORY *memory);
void initialise_memory(MEMORY *memory);
void execute_instruction(int clock, CPU *cpu, MEMORY *memory);
BYTE fetch_byte(int *clock, CPU *cpu, MEMORY *memory);
BYTE read_byte(int *clock, BYTE address, MEMORY *memory);
void lda_set_flags(CPU *cpu);

int main(void)
{
	CPU cpu;
	MEMORY memory;

	reset_cpu(&cpu, &memory);

	/* Start of simple test program */
	memory.data[0xFFFC] = INS_LDA_ZPX;
	memory.data[0xFFFD] = 0x42;
	cpu.x = 0x01;
	memory.data[0x43] = 0x23;
	execute_instruction(3, &cpu, &memory);
	/* End of simple test program */

	printf("Value in a: %d\n", cpu.a);

	return 0;
}

void reset_cpu(CPU *cpu, MEMORY *memory)
{
	cpu->pc = 0xFFFC;

	cpu->sp = 0x00FF;

	cpu->d = 0;

	initialise_memory(memory);
}

void initialise_memory(MEMORY *memory)
{
	for (unsigned int i = 0; i < MEMORY_SIZE; ++i)
	{
		memory->data[i] = 0;
	}
}

void execute_instruction(int clock, CPU *cpu, MEMORY *memory)
{
	BYTE instruction;
	BYTE zp_address;

	while (clock > 0)
	{
		instruction = fetch_byte(&clock, cpu, memory);
		switch(instruction)
		{
			case END:
			{
				printf("Reached the end.\n");
				clock = 0;
				break;
			}
			case INS_LDA_IM:
			{
				cpu->a = fetch_byte(&clock, cpu, memory);
				cpu->z = (cpu->a == 0);
				// Check if 7th bit of cpu->a is 1 (number is negative)
				cpu->n = ((cpu->a & (1 << 6)) > 0);
				break;
			}
			case INS_LDA_ZP:
			{
				zp_address = fetch_byte(&clock, cpu, memory);

				cpu->a = read_byte(&clock, zp_address, memory);
				lda_set_flags(cpu);

				break;
			}
			case INS_LDA_ZPX:
			{
				zp_address = fetch_byte(&clock, cpu, memory);

				zp_address += cpu->x;
				clock--;

				cpu->a = read_byte(&clock, zp_address, memory);
				lda_set_flags(cpu);

				break;
			}
		}
	}
}

BYTE fetch_byte(int *clock, CPU *cpu, MEMORY *memory)
{
	/*
	 * Fetches a byte from memory and uses a clock cycle
	 * Also increments the program counter
	*/
	BYTE data = memory->data[cpu->pc];
	cpu->pc++;
	*clock -= 1;
	return data;
}

BYTE read_byte(int *clock, BYTE address, MEMORY *memory)
{
	/*
	 * Fetches a byte from memory and uses a clock cylce
	 * Does NOT increment the program counter
	*/
	BYTE data = memory->data[address];
	*clock -= - 1;
	return data;
}

void lda_set_flags(CPU *cpu)
{
	/*
	 * Sets the appropriate flagsa when loading to cpu->a register
	*/
	cpu->z = (cpu->a == 0);
	// Check if 7th bit of cpu->a is 1 (number is negative)
	cpu->n = ((cpu->a & (1 << 6)) > 0);
}
