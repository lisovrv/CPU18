#ifndef CPU_COMPILER_H
#define CPU_COMPILER_H

#include "makebuffstr.h"

#define MAX_NUMBER_OF_LABELS 40
#define MAX_LAB_NAME 40
#define NAME_LENGTH 40
#define ARG_LENGTH  40
#define MAX_MEM_FOR_ONE_FUNC 6
#define VAL_TYPE 0
#define REG_TYPE 1
#define RAM_TYPE 2

struct Label
{
    const char name[MAX_LAB_NAME];
    int byte_code_adres;
};

extern struct Label labels[MAX_NUMBER_OF_LABELS];

void Compile(const char* asm_file_name);
void Push_Pop_Jmp_analisation(const char* line_, char** byte_code, int* ip);



#endif //CPU_COMPILER_H
