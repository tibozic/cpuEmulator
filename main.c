#include <math.h>
#include <string.h>
#include <assert.h>

#define STACK_OFFSET 0x0100

// 2^16
#define MEMORY_SIZE 1024 * 64

typedef unsigned char BYTE;
typedef short WORD;

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

// Functions
void reset_cpu(CPU *cpu, MEMORY *memory);
void initialise_memory(MEMORY *memory);
void execute_instruction(int clock, CPU *cpu, MEMORY *memory);
BYTE fetch(int *clock, CPU *cpu, MEMORY *memory);

int main(void)
{
	CPU cpu;
	MEMORY memory;

	reset_cpu(&cpu, &memory);

	memory.data[0xFFFC] = 0x00FF;
	execute_instruction(2, &cpu, &memory);

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
	while (clock > 0)
	{
		fetch(&clock, cpu, memory);
		fetch(&clock, cpu, memory);
	}
}

BYTE fetch(int *clock, CPU *cpu, MEMORY *memory)
{
	BYTE data = memory->data[cpu->pc];
	cpu->pc++;
	clock--;
	return data;
}
