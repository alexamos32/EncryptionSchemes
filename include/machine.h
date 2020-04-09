#ifndef CS4417_DEMO_MACHINE_H
#define CS4417_DEMO_MACHINE_H

#define INST_READ 0x00
#define INST_WRITE 0x01

#define INST_SET 0x10
#define INST_ADD 0x11
#define INST_ADDI 0x12
#define INST_SUB 0x13
#define INST_SUBI 0x14
#define INST_SHL 0x15
#define INST_SHR 0x16

#define INST_ANDI 0x20
#define INST_ORI 0x21
#define INST_XORI 0x22
#define INST_AND 0x23
#define INST_OR 0x24
#define INST_XOR 0x25

#define INST_ST 0x30
#define INST_LD 0x31
#define INST_STR 0x32
#define INST_LDR 0x33

#define INST_JMP 0xf0
#define INST_JZ 0xf1
#define INST_JNZ 0xf2
#define INST_HLT 0xff

#define REG(x) (x)
#define REGX 0

struct instruction {
	unsigned char op;
	unsigned reg1: 4;
	unsigned reg2: 4;
	unsigned reg3: 4;
	unsigned imm: 8;
};

struct reg {
	unsigned int val;
};

#endif //CS4417_DEMO_MACHINE_H
