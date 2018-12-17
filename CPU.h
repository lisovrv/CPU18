#ifndef CPU_CPU_H
#define CPU_CPU_H

#include "stack.h"
#include "makebuffstr.h"
#include "enum_cmd.h"

#define RAM_SIZE        20
#define STACK_SIZE      20
#define POISON          INT_MAX
#define VAL_TYPE        0
#define REG_TYPE        1
#define RAM_TYPE        2
#define START           99

struct Cpu
{
    Stack* stk;
    int REGS[REG_SIZE];
    int RAM[RAM_SIZE];
    Stack* stk_call;
    FILE* file_dump;
};

struct Cpu Cpu_Create();
void Cpu_Destruct(struct Cpu cpu);
void Run(struct Cpu cpu, char* byte_code, long file_size);
void Cpu_Dump(struct Cpu cpu, FILE* file_dump);

#endif //CPU_CPU_H
