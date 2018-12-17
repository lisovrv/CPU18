#include <string.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>

#include "CPU.h"

void Run(struct Cpu cpu, char* byte_code, long file_size)
{
    if(byte_code == nullptr)
    {
        printf("ptr is null!\n");
    }
    assert(byte_code);
    size_t ip = 0;
    if(byte_code[0] != CUR_VERSION)
    {
        printf("Version of cpu is outdated: %d, instead of %d in the byte_code"
                                                          , byte_code[0], CUR_VERSION);
    }
    while(byte_code[ip] != START)
    {
        ip++;
    }
    ip++;
    while(ip < file_size)
    {
        switch(byte_code[ip])
        {

            #define DEFCMD( name, value, arguments, code )              \
                case value:                                             \
                {                                                       \
                    code;                                               \
                    break;                                              \
                }
            #include "commands.h"
            default:
                break;
            #undef DEFCMD
        }
    }

    /*printf("byte_code :  ");
    for(int i = 0; i < file_size; i++)
    {
        printf("%d ", byte_code[i]);
    }
    printf("\n");*/
}

struct Cpu Cpu_Create()
{
    struct Cpu cpu;
    cpu.stk = new Stack(STACK_SIZE);
    cpu.stk_call = new Stack(STACK_SIZE);
    for(int i = 0; i < REG_SIZE; i++)
    {
        cpu.REGS[i] = -77;
    }
    for(int i = 0; i < RAM_SIZE; i++)
    {
        cpu.RAM[i] = -33;
    }
    cpu.file_dump = fopen("cpu_log.txt", "w+");
    return cpu;
}

void Cpu_Destruct(struct Cpu cpu)
{
    delete cpu.stk;
    delete cpu.stk_call;
    for(int i = 0; i < REG_SIZE; i++)
    {
        cpu.REGS[i] = POISON;
    }
    for(int i = 0; i < RAM_SIZE; i++)
    {
        cpu.RAM[i] = POISON;
    }
    fclose(cpu.file_dump);
}

void Cpu_Dump(struct Cpu cpu, FILE* file_dump)
{
    fprintf(file_dump, "--------------------------------------------------------------------\n");
    cpu.stk->Dump_term(file_dump);
    for(int i = 0; i < REG_SIZE; i++)
    {
        fprintf(file_dump, "reg[%d]=%d ", i, cpu.REGS[i]);
        cpu.REGS[i] = POISON;
    }
    fprintf(file_dump, "\n");
    fprintf(file_dump, "RAM: ");
    for(int i = 0; i < RAM_SIZE; i++)
    {
        fprintf(file_dump, "%d ", cpu.RAM[i]);
    }
    fprintf(file_dump, "\n");
    fprintf(file_dump, "--------------------------------------------------------------------\n");
}
