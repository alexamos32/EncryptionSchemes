#include <unistd.h>

#include "instruction.h"
#include "utils.h"

static int ex_read(struct instruction *instruction_reg, struct reg gp_reg[16], unsigned char memory[256], int *pc);
static int ex_write(struct instruction *instruction_reg, struct reg gp_reg[16], unsigned char memory[256], int *pc);
static int ex_set(struct instruction *instruction_reg, struct reg gp_reg[16], unsigned char memory[256], int *pc);
static int ex_add(struct instruction *instruction_reg, struct reg gp_reg[16], unsigned char memory[256], int *pc);
static int ex_addi(struct instruction *instruction_reg, struct reg gp_reg[16], unsigned char memory[256], int *pc);
static int ex_sub(struct instruction *instruction_reg, struct reg gp_reg[16], unsigned char memory[256], int *pc);
static int ex_subi(struct instruction *instruction_reg, struct reg gp_reg[16], unsigned char memory[256], int *pc);
static int ex_shl(struct instruction *instruction_reg, struct reg gp_reg[16], unsigned char memory[256], int *pc);
static int ex_shr(struct instruction *instruction_reg, struct reg gp_reg[16], unsigned char memory[256], int *pc);
static int ex_andi(struct instruction *instruction_reg, struct reg gp_reg[16], unsigned char memory[256], int *pc);
static int ex_ori(struct instruction *instruction_reg, struct reg gp_reg[16], unsigned char memory[256], int *pc);
static int ex_xori(struct instruction *instruction_reg, struct reg gp_reg[16], unsigned char memory[256], int *pc);
static int ex_and(struct instruction *instruction_reg, struct reg gp_reg[16], unsigned char memory[256], int *pc);
static int ex_or(struct instruction *instruction_reg, struct reg gp_reg[16], unsigned char memory[256], int *pc);
static int ex_xor(struct instruction *instruction_reg, struct reg gp_reg[16], unsigned char memory[256], int *pc);
static int ex_str(struct instruction *instruction_reg, struct reg gp_reg[16], unsigned char memory[256], int *pc);
static int ex_ldr(struct instruction *instruction_reg, struct reg gp_reg[16], unsigned char memory[256], int *pc);
static int ex_st(struct instruction *instruction_reg, struct reg gp_reg[16], unsigned char memory[256], int *pc);
static int ex_ld(struct instruction *instruction_reg, struct reg gp_reg[16], unsigned char memory[256], int *pc);
static int ex_jmp(struct instruction *instruction_reg, struct reg gp_reg[16], unsigned char memory[256], int *pc);
static int ex_jz(struct instruction *instruction_reg, struct reg gp_reg[16], unsigned char memory[256], int *pc);
static int ex_jnz(struct instruction *instruction_reg, struct reg gp_reg[16], unsigned char memory[256], int *pc);
static int ex_hlt(struct instruction *instruction_reg, struct reg gp_reg[16], unsigned char memory[256], int *pc);

int execute(struct instruction *instruction_reg, struct reg gp_reg[16], unsigned char memory[256], int *pc)
{
	switch (instruction_reg->op) {
		case INST_READ:
			return ex_read(instruction_reg, gp_reg, memory, pc);
		case INST_WRITE:
			return ex_write(instruction_reg, gp_reg, memory, pc);

		case INST_SET:
			return ex_set(instruction_reg, gp_reg, memory, pc);
		case INST_ADD:
			return ex_add(instruction_reg, gp_reg, memory, pc);
		case INST_ADDI:
			return ex_addi(instruction_reg, gp_reg, memory, pc);
		case INST_SUB:
			return ex_sub(instruction_reg, gp_reg, memory, pc);
		case INST_SUBI:
			return ex_subi(instruction_reg, gp_reg, memory, pc);
		case INST_SHL:
			return ex_shl(instruction_reg, gp_reg, memory, pc);
		case INST_SHR:
			return ex_shr(instruction_reg, gp_reg, memory, pc);

		case INST_ANDI:
			return ex_andi(instruction_reg, gp_reg, memory, pc);
		case INST_ORI:
			return ex_ori(instruction_reg, gp_reg, memory, pc);
		case INST_XORI:
			return ex_xori(instruction_reg, gp_reg, memory, pc);
		case INST_AND:
			return ex_and(instruction_reg, gp_reg, memory, pc);
		case INST_OR:
			return ex_or(instruction_reg, gp_reg, memory, pc);
		case INST_XOR:
			return ex_xor(instruction_reg, gp_reg, memory, pc);

		case INST_STR:
			return ex_str(instruction_reg, gp_reg, memory, pc);
		case INST_LDR:
			return ex_ldr(instruction_reg, gp_reg, memory, pc);
		case INST_ST:
			return ex_st(instruction_reg, gp_reg, memory, pc);
		case INST_LD:
			return ex_ld(instruction_reg, gp_reg, memory, pc);

		case INST_JMP:
			return ex_jmp(instruction_reg, gp_reg, memory, pc);
		case INST_JZ:
			return ex_jz(instruction_reg, gp_reg, memory, pc);
		case INST_JNZ:
			return ex_jnz(instruction_reg, gp_reg, memory, pc);
		case INST_HLT:
			return ex_hlt(instruction_reg, gp_reg, memory, pc);
	}

	return 0;
}

static int ex_read(struct instruction *instruction_reg, struct reg gp_reg[16], unsigned char memory[256], int *pc)
{
	(void) memory;
	(void) pc;

	char c;
	if (recoverable_read(STDIN_FILENO, &c, sizeof(char)) != sizeof(char))
		gp_reg[instruction_reg->reg2].val = 0;
	else
		gp_reg[instruction_reg->reg2].val = 1;
	gp_reg[instruction_reg->reg1].val = c;

	return 0;
}

static int ex_write(struct instruction *instruction_reg, struct reg gp_reg[16], unsigned char memory[256], int *pc)
{
	(void) memory;
	(void) pc;

	char c = (char) gp_reg[instruction_reg->reg1].val;
	if (recoverable_write(STDOUT_FILENO, &c, sizeof(char)) != sizeof(char))
		gp_reg[instruction_reg->reg2].val = 0;
	else
		gp_reg[instruction_reg->reg2].val = 1;

	return 0;
}

static int ex_set(struct instruction *instruction_reg, struct reg gp_reg[16], unsigned char memory[256], int *pc)
{
	(void) memory;
	(void) pc;

	gp_reg[instruction_reg->reg1].val = instruction_reg->imm;
	return 0;
}

static int ex_add(struct instruction *instruction_reg, struct reg gp_reg[16], unsigned char memory[256], int *pc)
{
	(void) memory;
	(void) pc;

	gp_reg[instruction_reg->reg1].val = gp_reg[instruction_reg->reg2].val + gp_reg[instruction_reg->reg3].val;
	return 0;
}

static int ex_addi(struct instruction *instruction_reg, struct reg gp_reg[16], unsigned char memory[256], int *pc)
{
	(void) memory;
	(void) pc;

	gp_reg[instruction_reg->reg1].val = gp_reg[instruction_reg->reg2].val + instruction_reg->imm;
	return 0;
}

static int ex_sub(struct instruction *instruction_reg, struct reg gp_reg[16], unsigned char memory[256], int *pc)
{
	(void) memory;
	(void) pc;

	gp_reg[instruction_reg->reg1].val = gp_reg[instruction_reg->reg2].val - gp_reg[instruction_reg->reg3].val;
	return 0;
}

static int ex_subi(struct instruction *instruction_reg, struct reg gp_reg[16], unsigned char memory[256], int *pc)
{
	(void) memory;
	(void) pc;

	gp_reg[instruction_reg->reg1].val = gp_reg[instruction_reg->reg2].val - instruction_reg->imm;
	return 0;
}

static int ex_shl(struct instruction *instruction_reg, struct reg gp_reg[16], unsigned char memory[256], int *pc)
{
	(void) memory;
	(void) pc;

	gp_reg[instruction_reg->reg1].val = gp_reg[instruction_reg->reg2].val << (unsigned)instruction_reg->imm;
	return 0;
}

static int ex_shr(struct instruction *instruction_reg, struct reg gp_reg[16], unsigned char memory[256], int *pc)
{
	(void) memory;
	(void) pc;

	gp_reg[instruction_reg->reg1].val = gp_reg[instruction_reg->reg2].val >> (unsigned)instruction_reg->imm;
	return 0;
}

static int ex_andi(struct instruction *instruction_reg, struct reg gp_reg[16], unsigned char memory[256], int *pc)
{
	(void) memory;
	(void) pc;

	gp_reg[instruction_reg->reg1].val = gp_reg[instruction_reg->reg2].val & instruction_reg->imm;
	return 0;
}

static int ex_ori(struct instruction *instruction_reg, struct reg gp_reg[16], unsigned char memory[256], int *pc)
{
	(void) memory;
	(void) pc;

	gp_reg[instruction_reg->reg1].val = gp_reg[instruction_reg->reg2].val | instruction_reg->imm;
	return 0;
}

static int ex_xori(struct instruction *instruction_reg, struct reg gp_reg[16], unsigned char memory[256], int *pc)
{
	(void) memory;
	(void) pc;

	gp_reg[instruction_reg->reg1].val = gp_reg[instruction_reg->reg2].val ^ instruction_reg->imm;
	return 0;
}

static int ex_and(struct instruction *instruction_reg, struct reg gp_reg[16], unsigned char memory[256], int *pc)
{
	(void) memory;
	(void) pc;

	gp_reg[instruction_reg->reg1].val = gp_reg[instruction_reg->reg2].val & gp_reg[instruction_reg->reg3].val;
	return 0;
}

static int ex_or(struct instruction *instruction_reg, struct reg gp_reg[16], unsigned char memory[256], int *pc)
{
	(void) memory;
	(void) pc;

	gp_reg[instruction_reg->reg1].val = gp_reg[instruction_reg->reg2].val | gp_reg[instruction_reg->reg3].val;
	return 0;
}

static int ex_xor(struct instruction *instruction_reg, struct reg gp_reg[16], unsigned char memory[256], int *pc)
{
	(void) memory;
	(void) pc;

	gp_reg[instruction_reg->reg1].val = gp_reg[instruction_reg->reg2].val ^ gp_reg[instruction_reg->reg3].val;
	return 0;
}

static int ex_str(struct instruction *instruction_reg, struct reg gp_reg[16], unsigned char memory[256], int *pc)
{
	(void) pc;

	memory[gp_reg[instruction_reg->reg2].val] = gp_reg[instruction_reg->reg1].val;
	return 0;
}

static int ex_ldr(struct instruction *instruction_reg, struct reg gp_reg[16], unsigned char memory[256], int *pc)
{
	(void) pc;

	gp_reg[instruction_reg->reg1].val = memory[gp_reg[instruction_reg->reg2].val];
	return 0;
}

static int ex_st(struct instruction *instruction_reg, struct reg gp_reg[16], unsigned char memory[256], int *pc)
{
	(void) pc;

	memory[gp_reg[instruction_reg->reg2].val] = instruction_reg->imm;
	return 0;
}

static int ex_ld(struct instruction *instruction_reg, struct reg gp_reg[16], unsigned char memory[256], int *pc)
{
	(void) pc;

	gp_reg[instruction_reg->imm].val = memory[gp_reg[instruction_reg->reg2].val];
	return 0;
}

static int ex_jmp(struct instruction *instruction_reg, struct reg gp_reg[16], unsigned char memory[256], int *pc)
{
	(void) gp_reg;
	(void) memory;

	*pc = (int)instruction_reg->imm;
	return 0;
}

static int ex_jz(struct instruction *instruction_reg, struct reg gp_reg[16], unsigned char memory[256], int *pc)
{
	(void) memory;

	if (!gp_reg[instruction_reg->reg1].val)
		*pc = (int)instruction_reg->imm;
	return 0;
}

static int ex_jnz(struct instruction *instruction_reg, struct reg gp_reg[16], unsigned char memory[256], int *pc)
{
	(void) memory;

	if (gp_reg[instruction_reg->reg1].val)
		*pc = (int)instruction_reg->imm;
	return 0;
}

static int ex_hlt(struct instruction *instruction_reg, struct reg gp_reg[16], unsigned char memory[256], int *pc)
{
	(void) instruction_reg;
	(void) gp_reg;
	(void) memory;
	(void) pc;

	return 1;
}
