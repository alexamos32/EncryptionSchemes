#ifndef CS4417_PROJECT_DEMO_INSTRUCTION_H
#define CS4417_PROJECT_DEMO_INSTRUCTION_H

#ifndef CS4417_DEMO_MACHINE_H
#include "machine.h"
#endif

int execute(struct instruction *instruction_reg, struct reg gp_reg[16], unsigned char memory[256], int *pc);

#endif //CS4417_PROJECT_DEMO_INSTRUCTION_H
