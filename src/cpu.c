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

	BYTE temp_data;

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
				byte_push(&clock, cpu->a, cpu, memory);

				break;
			}
			case INS_PLA:
			{
				cpu->a = byte_pop(&clock, cpu, memory);

				cpu_ld_set_flags(cpu, cpu->a);

				break;
			}
			case INS_PLP:
			{
				temp_data = byte_pop(&clock, cpu, memory);


				cpu->c = (temp_data & 0b00000001) > 0;
				cpu->z = (temp_data & 0b00000010) > 0;
				cpu->i = (temp_data & 0b00000100) > 0;
				cpu->d = (temp_data & 0b00001000) > 0;
				cpu->b = (temp_data & 0b00010000) > 0;
				cpu->v = (temp_data & 0b00100000) > 0;
				cpu->n = (temp_data & 0b01000000) > 0;

				break;
			}
			case INS_PHP:
			{
				temp_data = 0x0;

				temp_data = (temp_data | cpu->c) << 1;
				temp_data = (temp_data | cpu->z) << 1;
				temp_data = (temp_data | cpu->i) << 1;
				temp_data = (temp_data | cpu->d) << 1;
				temp_data = (temp_data | cpu->b) << 1;
				temp_data = (temp_data | cpu->v) << 1;
				temp_data = (temp_data | cpu->n) << 1;

				byte_push(&clock, temp_data, cpu, memory);

				break;
			}
			case INS_AND_IM:
			{
				cpu->a &= byte_read(&clock, cpu->pc, memory);

				cpu_ld_set_flags(cpu, cpu->a);

				break;
			}
			case INS_AND_ZP:
		{
				zp_address = byte_fetch(&clock, cpu, memory);

				temp_data = byte_read(&clock, zp_address, memory);

				cpu->a &= temp_data;

				cpu_ld_set_flags(cpu, cpu->a);

				break;
			}
			case INS_AND_ZPX:
			{
				zp_address = byte_fetch(&clock, cpu, memory);

				zp_addressx = zp_address + cpu->x;
				clock++;

				temp_data = byte_read(&clock, zp_addressx, memory);

				cpu->a &= temp_data;

				cpu_ld_set_flags(cpu, cpu->a);

				break;
			}
			case INS_AND_ABS:
			{
				abs_address = word_fetch(&clock, cpu, memory);

				temp_data = byte_read(&clock, abs_address, memory);

				cpu->a &= temp_data;

				cpu_ld_set_flags(cpu, cpu->a);

				break;
			}
			case INS_AND_ABSX:
			{
				abs_address = word_fetch(&clock, cpu, memory);

				abs_addressx = abs_address + cpu->x;
				clock++;

				crossed_page_boundry = (abs_address ^ abs_addressx) >> 8;
				if ( !crossed_page_boundry )
				{
					clock--;
				}

				temp_data = byte_read(&clock, abs_addressx, memory);

				cpu->a &= temp_data;

				cpu_ld_set_flags(cpu, cpu->a);

				break;
			}
			case INS_AND_ABSY:
			{
				abs_address = word_fetch(&clock, cpu, memory);

				abs_addressx = abs_address + cpu->y;
				clock++;

				crossed_page_boundry = (abs_address ^ abs_addressx) >> 8;
				if ( !crossed_page_boundry )
				{
					clock--;
				}

				temp_data = byte_read(&clock, abs_addressx, memory);

				cpu->a &= temp_data;

				cpu_ld_set_flags(cpu, cpu->a);

				break;
			}
			case INS_AND_INDX:
			{
				zp_address = byte_fetch(&clock, cpu, memory);

				zp_addressx = zp_address + cpu->x;
				clock++;

				abs_address = word_read(&clock, zp_addressx, memory);

				temp_data = byte_read(&clock, abs_address, memory);

				cpu->a &= temp_data;

				cpu_ld_set_flags(cpu, cpu->a);

				break;
			}
			case INS_AND_INDY:
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

				cpu->a &= byte_read(&clock, abs_addressx, memory);

				cpu_ld_set_flags(cpu, cpu->a);

				break;
			}
			case INS_JSR:
			{
				abs_address = word_fetch(&clock, cpu, memory);

				word_write(&clock,
						   STACK_OFFSET + cpu->sp,
						   cpu->pc - 1,
						   memory);
				cpu->sp -= 2;
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

BYTE byte_pop(int *clock, CPU *cpu, MEMORY *memory)
{
	/*
	 * Pops a byte of data from the stack
	*/

	// SP is pointing at the next free locations, we first need to increment
	// it to get the next taken location
	cpu->sp++;
	(*clock)++;

	BYTE data = memory->data[STACK_OFFSET + cpu->sp];
	(*clock)++;

	// TODO: Where does an extra cycle come from??
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

void byte_push(int *clock, BYTE data, CPU *cpu, MEMORY *memory)
{
	/*
	 * Pushes a byte of data to the stack
	*/

	memory->data[STACK_OFFSET + cpu->sp] = data;
	(*clock)++;

	cpu->sp--;
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

void memory_print(MEMORY *memory, int start, int end)
{
	assert(end <= MEMORY_SIZE);
	for (int i = start; i < end; ++i)
	{
		printf("MEMORY[0x%x] = 0x%x\n", i, memory->data[i]);
	}
}
