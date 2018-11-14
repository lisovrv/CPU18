#ifndef CPU_COMPILER_H
#define CPU_COMPILER_H

#include "makebuffstr.h"

#define name_limit      10
#define argument_limit  30

typedef struct Command
{
    char name[name_limit];
    char argument[argument_limit];
}Command;

class Compiler
{
    Verificator verificator;
    Make_buff make_buff;

    //String_view* Text_to_strings(FILE *file_asm, int* count_of_lines);
    //void Scaning_commands(String_view* strings, int count_of_lines);


public:
    void Compile(FILE* file_asm);


};



#endif //CPU_COMPILER_H
