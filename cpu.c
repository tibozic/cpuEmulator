#include "cpu.h"

void reset_cpu(CPU *cpu, MEMORY *memory)
{
	cpu->pc = 0xFFFC;

	// With stack offset this is 0x01FF
	cpu->sp = 0xFF;

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
	WORD abs_address;

	while (clock > 0)
	{
		instruction = fetch_byte(&clock, cpu, memory);
		switch(instruction)
		{
			case INS_LDA_IM:
			{
				cpu->a = fetch_byte(&clock, cpu, memory);

				load_set_flags(cpu, cpu->a);

				break;
			}
			case INS_LDA_ZP:
			{
				zp_address = fetch_byte(&clock, cpu, memory);

				cpu->a = read_byte(&clock, zp_address, memory);

				load_set_flags(cpu, cpu->a);

				break;
			}
			case INS_LDA_ZPX:
			{
				zp_address = fetch_byte(&clock, cpu, memory);

				zp_address += cpu->x;
				clock--;

				cpu->a = read_byte(&clock, zp_address, memory);
				load_set_flags(cpu, cpu->a);

				break;
			}
			case INS_STA_ZP:
			{
				zp_address = fetch_byte(&clock, cpu, memory);

				memory->data[zp_address] = cpu->a;

				write_byte(&clock, zp_address, cpu->a, cpu, memory);

				break;
			}
			case INS_LDX_IM:
			{
				cpu->a = fetch_byte(&clock, cpu, memory);

				load_set_flags(cpu, cpu->x);

				break;
			}
			case INS_LDX_ZP:
			{
				zp_address = fetch_byte(&clock, cpu, memory);

				cpu->a = read_byte(&clock, zp_address, memory);

				load_set_flags(cpu, cpu->x);

				break;
			}
			case INS_LDX_ZPX:
			{
				zp_address = fetch_byte(&clock, cpu, memory);

				zp_address += cpu->x;
				clock--;

				cpu->a = read_byte(&clock, zp_address, memory);
				load_set_flags(cpu, cpu->x);

				break;
			}
			case INS_LDX_ABS:
			{
				abs_address = fetch_word(&clock, cpu, memory);
				cpu->a = (BYTE) read_word(&clock, abs_address, memory);

				load_set_flags(cpu, cpu->x);

				break;
			}
			case INS_JSR:
			{
				abs_address = fetch_word(&clock, cpu, memory);

				write_word(&clock,
						   STACK_OFFSET + cpu->sp,
						   cpu->pc - 1,
						   memory);
				cpu->sp--;
				clock--;

				cpu->pc = abs_address;
				clock--;

				break;
			}
			default:
			{
				printf("Instruction unknown: 0x%x\n", instruction);
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

void write_byte(int *clock, BYTE address, BYTE value, CPU *cpu, MEMORY *memory)
{
	/*
	 * Writes a byte to memory
	 * Uses 1 clock cycle
	 * Increments the program counter
	*/
	memory->data[address] = value;
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

BYTE read_word(int *clock, WORD address, MEMORY *memory)
{
	/*
	 * Fetches a word from memory
	 * Uses 2 clock cycles
	*/
	WORD data = memory->data[address];
	*clock -= 1;

	data |= (memory->data[address + 1] << 8);
	*clock -= 1;

	printf("Used 2 clock cycle for reading word.\n");
	*clock -= - 1;

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

void load_set_flags(CPU *cpu, BYTE register_data)
{
	/*
	 * Sets the appropriate flags when loading to a register
	*/
	cpu->z = (register_data == 0);
	// Check if 7th bit of cpu->a is 1 (number is negative)
	cpu->n = ((register_data & (1 << 6)) > 0);
}

void print_memory(MEMORY *memory, int start, int end)
{
	assert(end <= MEMORY_SIZE);
	for (int i = start; i < end; ++i)
	{
		printf("MEMORY[0x%x] = 0x%x\n", i, memory->data[i]);
	}
}
