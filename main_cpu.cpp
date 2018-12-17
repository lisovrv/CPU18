#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#include <assert.h>

#include "CPU.h"

int main()
{
    long file_size = Sizeof_file("byte_code.bin");
    FILE* byte_code_file = fopen("byte_code.bin", "rb");
    if(byte_code_file == nullptr)
    {
        printf("ptr is null!\n");
    }
    assert(byte_code_file);
    char* byte_code = (char*) calloc((size_t)file_size, sizeof(char));
    fread(byte_code, sizeof(char), (size_t)file_size, byte_code_file);
    fclose(byte_code_file);

    struct Cpu cpu = Cpu_Create();
    Run(cpu, byte_code, file_size);
    Cpu_Destruct(cpu);
    free(byte_code);
    return 0;
}
