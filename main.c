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
#define INS_STA_ZP 0x85
#define END 0x0

// Functions
void reset_cpu(CPU *cpu, MEMORY *memory);
void initialise_memory(MEMORY *memory);
void execute_instruction(int clock, CPU *cpu, MEMORY *memory);
BYTE fetch_byte(int *clock, CPU *cpu, MEMORY *memory);
BYTE read_byte(int *clock, BYTE address, MEMORY *memory);
void write_byte(int *clock, BYTE address, CPU *cpu, MEMORY *memory);
WORD fetch_word(int *clock, CPU *cpu, MEMORY *memory);
void write_word(int *clock, WORD address, WORD value, MEMORY *memory);
void lda_set_flags(CPU *cpu);
void print_memory(MEMORY *memory, int start);

int main(void)
{
	CPU cpu;
	MEMORY memory;

	reset_cpu(&cpu, &memory);

	/* Start of simple test program */
	cpu.a = 0x60;
	memory.data[0xFFFC] = INS_STA_ZP;
	memory.data[0xFFFD] = 0x42;
	memory.data[0xFFFE] = INS_LDA_ZP;
	memory.data[0xFFFF] = 0x42;
	execute_instruction(10, &cpu, &memory);
	/* End of simple test program */

	print_memory(&memory, MEMORY_SIZE - 5);
	printf("Value of a: 0x%x\n", cpu.a);
	printf("Value of address 0x42: 0x%x\n", memory.data[0x42]);

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
			case INS_STA_ZP:
			{
				zp_address = fetch_byte(&clock, cpu, memory);
				memory->data[zp_address] = cpu->a;

				write_byte(&clock, zp_address, cpu, memory);

				break;
			}
		}
	}
}

BYTE fetch_byte(int *clock, CPU *cpu, MEMORY *memory)
{
	/*
	 * Fetches a byte from memory
	 * Uses 1 clock cycle
	 * Increments the program counter
	*/
	BYTE data = memory->data[cpu->pc];
	cpu->pc++;
	printf("Used 1 clock cycle for fetching byte.\n");
	*clock -= 1;
	return data;
}

BYTE read_byte(int *clock, BYTE address, MEMORY *memory)
{
	/*
	 * Fetches a byte from memory
	 * Uses 1 clock cylce
	*/
	BYTE data = memory->data[address];
	printf("Used 1 clock cycle for reading byte.\n");
	*clock -= - 1;
	return data;
}

void write_byte(int *clock, BYTE address, CPU *cpu, MEMORY *memory)
{
	/*
	 * Writes a byte to memory
	 * Uses 1 clock cycle
	 * Increments the program counter
	*/
	memory->data[address] = cpu->a;
	cpu->pc++;
	printf("Used 1 cycle for writing byte.\n");
	*clock -= 1;
}

WORD fetch_word(int *clock, CPU *cpu, MEMORY *memory)
{
	/*
	 * Fetches a word from memory
	 * Uses 2 clock cycles
	 * Increments the program counter
	*/
	// Little endian
	WORD data = memory->data[cpu->pc];
	cpu->pc++;
	*clock -= 1;

	data |= (memory->data[cpu->pc] << 8);
	cpu->pc++;
	*clock -= 1;

	printf("Used 2 clock cylces for fetching a word.\n");
	return data;
}

void write_word(int *clock, WORD address, WORD value, MEMORY *memory)
{
	/*
	 * Writes a word to memory
	 * Uses 2 clock cycles
	*/
	memory->data[address]		= (value & 0xFF);
	*clock -= 1;
	memory->data[address + 1]	= (value >> 8);
	*clock -= 1;
	printf("Used 2 clock cycles for writing a word.\n");
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

void print_memory(MEMORY *memory, int start)
{
	for (int i = start; i < MEMORY_SIZE; ++i)
	{
		printf("MEMORY[0x%x] = 0x%x\n", i, memory->data[i]);
	}
}
