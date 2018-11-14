#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#include <assert.h>

#include "CPU.h"
#include "Compiler.h"


int main()
{
    FILE* file_asm = fopen("asm.txt", "r");
    assert(file_asm);

    Compiler cmp = Compiler();
    cmp.Compile(file_asm);

    //CPU cpu = CPU();
    //cpu.Cpu();


    return 0;
}


