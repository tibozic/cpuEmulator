#include "cpu.h"

void cpu_reset(CPU *cpu, MEMORY *memory)
{
	/* Reset the CPU to it's initial state */
	cpu->pc = 0xFFFC;

	cpu->sp = 0xFF; // With stack offset this is 0x01FF

	cpu->d = 0;

	memory_initialise(memory);
}

void memory_initialise(MEMORY *memory)
{
	/* Initialise all memory to zero */
	for (unsigned int i = 0; i < MEMORY_SIZE; ++i)
	{
		memory->data[i] = 0;
	}
}

int instruction_execute(CPU *cpu, MEMORY *memory)
{
	BYTE instruction;
	BYTE zp_address;
	BYTE zp_addressx;
	WORD abs_address;
	WORD abs_addressx;
	bool crossed_page_boundry;

	bool ended = false;
	int clock = 0;

	while (!ended)
	{
		instruction = byte_fetch(&clock, cpu, memory);
		switch(instruction)
		{
			case INS_LDA_IM:
			{
				cpu->a = byte_fetch(&clock, cpu, memory);

				cpu_ld_set_flags(cpu, cpu->a);

				break;
			}
			case INS_LDA_ZP:
			{
				zp_address = byte_fetch(&clock, cpu, memory);

				cpu->a = byte_read(&clock, zp_address, memory);

				cpu_ld_set_flags(cpu, cpu->a);

				break;
			}
			case INS_LDA_ZPX:
			{
				zp_address = byte_fetch(&clock, cpu, memory);

				zp_address += cpu->x;
				clock++;

				cpu->a = byte_read(&clock, zp_address, memory);
				cpu_ld_set_flags(cpu, cpu->a);

				break;
			}
			case INS_LDA_ABS:
			{
				abs_address = word_fetch(&clock, cpu, memory);
				cpu->a = byte_read(&clock, abs_address, memory);

				cpu_ld_set_flags(cpu, cpu->a);

				break;
			}
			case INS_LDA_ABSX:
			{
				abs_address = word_fetch(&clock, cpu, memory);

				abs_addressx = abs_address + cpu->x;
				clock++;

				crossed_page_boundry = (abs_address ^ abs_addressx) >> 8;
				if ( !crossed_page_boundry )
				{
					clock--;
				}

				cpu->a = byte_read(&clock, abs_addressx, memory);

				cpu_ld_set_flags(cpu, cpu->a);

				break;
			}
			case INS_LDA_ABSY:
			{
				abs_address = word_fetch(&clock, cpu, memory);

				abs_addressx = abs_address + cpu->y;
				clock++;

				crossed_page_boundry = (abs_address ^ abs_addressx) >> 8;
				if ( !crossed_page_boundry )
				{
					clock--;
				}

				cpu->a = byte_read(&clock, abs_addressx, memory);

				cpu_ld_set_flags(cpu, cpu->a);

				break;
			}
			case INS_LDA_INDX:
			{
				zp_address = byte_fetch(&clock, cpu, memory);

				zp_addressx = zp_address + cpu->x;
				clock++;

				abs_address = word_read(&clock, zp_addressx, memory);

				cpu->a = byte_read(&clock, abs_address, memory);

				cpu_ld_set_flags(cpu, cpu->a);

				break;
			}
			case INS_LDA_INDY:
			{
				zp_address = byte_fetch(&clock, cpu, memory);

				abs_address = word_read(&clock, zp_address, memory);

				abs_addressx = abs_address + cpu->y;
				clock++;

				crossed_page_boundry = (abs_address ^ abs_addressx) >> 8;
				if ( !crossed_page_boundry )
				{
					clock--;
				}

				cpu->a = byte_read(&clock, abs_addressx, memory);

				cpu_ld_set_flags(cpu, cpu->a);

				break;
			}
			case INS_LDX_IM:
			{
				cpu->x = byte_fetch(&clock, cpu, memory);

				cpu_ld_set_flags(cpu, cpu->x);

				break;
			}
			case INS_LDX_ZP:
			{
				zp_address = byte_fetch(&clock, cpu, memory);

				cpu->x = byte_read(&clock, zp_address, memory);

				cpu_ld_set_flags(cpu, cpu->x);

				break;
			}
			case INS_LDX_ZPY:
			{
				zp_address = byte_fetch(&clock, cpu, memory);

				zp_address += cpu->y;
				clock++;

				cpu->x = byte_read(&clock, zp_address, memory);
				cpu_ld_set_flags(cpu, cpu->x);

				break;
			}
			case INS_LDX_ABS:
			{
				abs_address = word_fetch(&clock, cpu, memory);
				cpu->x = byte_read(&clock, abs_address, memory);

				cpu_ld_set_flags(cpu, cpu->x);

				break;
			}
			case INS_LDX_ABSY:
			{
				abs_address = word_fetch(&clock, cpu, memory);

				abs_addressx = abs_address + cpu->y;
				clock++;

				crossed_page_boundry = (abs_address ^ abs_addressx) >> 8;
				if ( !crossed_page_boundry )
				{
					clock--;
				}

				cpu->x = byte_read(&clock, abs_addressx, memory);

				cpu_ld_set_flags(cpu, cpu->x);

				break;
			}
			case INS_LDY_IM:
			{
				cpu->y = byte_fetch(&clock, cpu, memory);

				cpu_ld_set_flags(cpu, cpu->y);

				break;
			}
			case INS_LDY_ZP:
			{
				zp_address = byte_fetch(&clock, cpu, memory);

				cpu->y = byte_read(&clock, zp_address, memory);

				cpu_ld_set_flags(cpu, cpu->y);

				break;
			}
			case INS_LDY_ZPX:
			{
				zp_address = byte_fetch(&clock, cpu, memory);

				zp_address += cpu->x;
				clock++;

				cpu->y = byte_read(&clock, zp_address, memory);
				cpu_ld_set_flags(cpu, cpu->y);

				break;
			}
			case INS_LDY_ABS:
			{
				abs_address = word_fetch(&clock, cpu, memory);
				cpu->y = byte_read(&clock, abs_address, memory);

				cpu_ld_set_flags(cpu, cpu->y);

				break;
			}
			case INS_LDY_ABSX:
			{
				abs_address = word_fetch(&clock, cpu, memory);

				abs_addressx = abs_address + cpu->x;
				clock++;

				crossed_page_boundry = (abs_address ^ abs_addressx) >> 8;
				if ( !crossed_page_boundry )
				{
					clock--;
				}

				cpu->y = byte_read(&clock, abs_addressx, memory);

				cpu_ld_set_flags(cpu, cpu->y);

				break;
			}
			case INS_STA_ZP:
			{
				zp_address = byte_fetch(&clock, cpu, memory);

				byte_write(&clock, zp_address, cpu->a, cpu, memory);

				break;
			}
			case INS_STA_ZPX:
			{
				zp_address = byte_fetch(&clock, cpu, memory);

				zp_addressx = zp_address + cpu->x;
				clock++;

				byte_write(&clock, zp_addressx, cpu->a, cpu, memory);

				break;
			}
			case INS_STA_ABS:
			{
				abs_address = word_fetch(&clock, cpu, memory);

				byte_write(&clock, abs_address, cpu->a, cpu, memory);

				break;
			}
			case INS_STA_ABSX:
			{
				abs_address = word_fetch(&clock, cpu, memory);

				abs_addressx = abs_address + cpu->x;
				clock++;

				byte_write(&clock, abs_addressx, cpu->a, cpu, memory);

				break;
			}
			case INS_STA_ABSY:
			{
				abs_address = word_fetch(&clock, cpu, memory);

				abs_addressx = abs_address + cpu->y;
				clock++;

				byte_write(&clock, abs_addressx, cpu->a, cpu, memory);

				break;
			}
			case INS_STA_INDX:
			{
				zp_address = byte_fetch(&clock, cpu, memory);

				zp_addressx = zp_address + cpu->x;
				clock++;

				abs_address = word_read(&clock, zp_addressx, memory);

				byte_write(&clock, abs_address, cpu->a, cpu, memory);

				break;
			}
			case INS_STA_INDY:
			{
				zp_address = byte_fetch(&clock, cpu, memory);

				abs_address = word_read(&clock, zp_address, memory);

				abs_addressx = abs_address + cpu->y;
				clock++;

				byte_write(&clock, abs_addressx, cpu->a, cpu, memory);

				break;
			}
			case INS_STX_ZP:
			{
				zp_address = byte_fetch(&clock, cpu, memory);

				byte_write(&clock, zp_address, cpu->x, cpu, memory);

				break;
			}
			case INS_STX_ZPY:
			{
				zp_address = byte_fetch(&clock, cpu, memory);

				zp_addressx = zp_address + cpu->y;
				clock++;

				byte_write(&clock, zp_addressx, cpu->x, cpu, memory);

				break;
			}
			case INS_STX_ABS:
			{
				abs_address = word_fetch(&clock, cpu, memory);

				byte_write(&clock, abs_address, cpu->x, cpu, memory);

				break;
			}
			case INS_STY_ZP:
			{
				zp_address = byte_fetch(&clock, cpu, memory);

				byte_write(&clock, zp_address, cpu->y, cpu, memory);

				break;
			}
			case INS_STY_ZPX:
			{
				zp_address = byte_fetch(&clock, cpu, memory);

				zp_addressx = zp_address + cpu->x;
				clock++;

				byte_write(&clock, zp_addressx, cpu->y, cpu, memory);

				break;
			}
			case INS_STY_ABS:
			{
				abs_address = word_fetch(&clock, cpu, memory);

				byte_write(&clock, abs_address, cpu->y, cpu, memory);

				break;
			}
			case INS_TAX:
			{
				cpu->x = cpu->a;
				clock++;

				cpu_ld_set_flags(cpu, cpu->x);

				break;
			}
			case INS_TAY:
			{
				cpu->y = cpu->a;
				clock++;

				cpu_ld_set_flags(cpu, cpu->y);

				break;
			}
			case INS_TXA:
			{
				cpu->a = cpu->x;
				clock++;

				cpu_ld_set_flags(cpu, cpu->a);

				break;
			}
			case INS_TYA:
			{
				cpu->a = cpu->y;
				clock++;

				cpu_ld_set_flags(cpu, cpu->a);

				break;
			}
			case INS_TSX:
			{
				cpu->x = cpu->sp;
				clock++;

				cpu_ld_set_flags(cpu, cpu->x);

				break;
			}
			case INS_TXS:
			{
				cpu->sp = cpu->x;
				clock++;

				break;
			}
			case INS_PHA:
			{
				byte_write(&clock,
						   (STACK_OFFSET + cpu->sp),
						   cpu->a,
						   cpu,
						   memory);

				cpu->sp--;
				clock++;

				break;
			}
			case INS_JSR:
			{
				abs_address = word_fetch(&clock, cpu, memory);

				word_write(&clock,
						   STACK_OFFSET + cpu->sp,
						   cpu->pc - 1,
						   memory);
				cpu->sp--;
				clock++;

				cpu->pc = abs_address;
				clock++;

				break;
			}
			default:
			{
				// printf("Instruction unknown: 0x%x\n", instruction);
				// We fetched an unnecessary instruction, so it doesn't
				// actually count
				clock--;
				ended = true;
				break;
			}
		}
	}

	return clock;
}

BYTE byte_fetch(int *clock, CPU *cpu, MEMORY *memory)
{
	/*
	 * Fetches a byte from memory
	 * Uses 1 clock cycle
	 * Increments the program counter
	*/

	BYTE data = memory->data[cpu->pc];
	cpu->pc++;
	(*clock)++;

	return data;
}

BYTE byte_read(int *clock, WORD address, MEMORY *memory)
{
	/*
	 * Fetches a byte from memory
	 * Uses 1 clock cylce
	*/

	BYTE data = memory->data[address];
	(*clock)++;

	return data;
}

void byte_write(int *clock, WORD address, BYTE value, CPU *cpu, MEMORY *memory)
{
	/*
	 * Writes a byte to memory
	 * Uses 1 clock cycle
	 * Increments the program counter
	*/

	memory->data[address] = value;
	cpu->pc++;
	(*clock)++;
}

WORD word_fetch(int *clock, CPU *cpu, MEMORY *memory)
{
	/*
	 * Fetches a word from memory
	 * Uses 2 clock cycles
	 * Increments the program counter
	*/

	// Little endian
	WORD data = memory->data[cpu->pc];
	cpu->pc++;
	(*clock)++;

	data |= (memory->data[cpu->pc] << 8);
	cpu->pc++;
	(*clock)++;

	return data;
}

WORD word_read(int *clock, WORD address, MEMORY *memory)
{
	/*
	 * Fetches a word from memory
	 * Uses 2 clock cycles
	*/

	WORD data = memory->data[address];
	(*clock)++;

	data |= (memory->data[address + 1] << 8);
	(*clock)++;

	return data;
}

void word_write(int *clock, WORD address, WORD value, MEMORY *memory)
{
	/*
	 * Writes a word to memory
	 * Uses 2 clock cycles
	*/

	memory->data[address] = (value & 0xFF);
	(*clock)++;
	memory->data[address + 1] = (value >> 8);
	(*clock)++;

}

void cpu_ld_set_flags(CPU *cpu, BYTE register_data)
{
	/*
	 * Sets the appropriate flags when loading to a register
	*/

	cpu->z = (register_data == 0);

	/* if 7th bit of register is 1, the number is negative */
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
