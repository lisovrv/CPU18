#include <string.h>
#include "enum_cmd.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "Compiler.h"

struct Label labels[MAX_NUMBER_OF_LABELS] = {};

void Compile(const char* asm_file_name)
{
    if(asm_file_name == nullptr)
    {
        printf("ptr is null!\n");
    }
    assert(asm_file_name);
    size_t count_lines = 0;
    const char** lines = Text_to_lines(asm_file_name, &count_lines);
    char* byte_code = (char*) calloc(count_lines * MAX_MEM_FOR_ONE_FUNC, sizeof(char));

    char* buf_for_name = (char*) calloc(NAME_LENGTH, sizeof(char));
    int cur_number_of_labels = 0;
    int ip = 0;
    byte_code[ip] = CUR_VERSION; // the first byte will be about current version , e.g. : "-4"
    ip++;
    for(int i = 0; i < count_lines; i++)
    {
        sscanf(lines[i], "%s", buf_for_name);
        if(lines[i][0] == '\0' || lines[i][0] == ' ' || lines[i][0] == ';' );
        else if(buf_for_name[strlen(buf_for_name) - 1] == ':')
        {
            strncpy((char*)labels[cur_number_of_labels].name, (const char*) buf_for_name,
                    strlen(buf_for_name) - 1);
            labels[cur_number_of_labels].byte_code_adres = ip;
            cur_number_of_labels++;
        }
        #define DEFCMD( name, value, arguments, code )                                   \
                else if(strcasecmp(buf_for_name, #name) == 0)                            \
                {                                                                        \
                    byte_code[ip] = value;                                               \
                    ip++;                                                                \
                    if(arguments == 1)                                                   \
                    {                                                                    \
                        Push_Pop_Jmp_analisation(lines[i], &byte_code, &ip);             \
                    }                                                                    \
                }
        #include "commands.h"
        #undef DEFCMD
    }
    free((void*)lines[0]);
    free(lines);
    free(buf_for_name);

    FILE* byte_code_file = fopen("byte_code.bin", "wb");
    fwrite(byte_code, sizeof(char), (size_t)ip, byte_code_file);
    fclose(byte_code_file);
    /*printf("byte_code :  ");
    for(int i = 0; i < ip; i++)
    {
        printf("%d ", byte_code[i]);
    }
    printf("\n");*/

    free(byte_code);
}

void Push_Pop_Jmp_analisation(const char* line_, char** byte_code, int* ip)
{
    if(line_ == nullptr)
    {
        printf("ptr is null!\n");
    }
    if(byte_code == nullptr)
    {
        printf("ptr is null!\n");
    }
    if(ip == nullptr)
    {
        printf("ptr is null!\n");
    }
    assert(line_);
    assert(byte_code);
    assert(ip);
    int argument = 0;
    char* argument_str = (char*) calloc(ARG_LENGTH, sizeof(char));
    if(sscanf(line_, "%*s%d", &argument) == 1)
    {
        (*byte_code)[*ip] = VAL_TYPE;                                            \
        (*ip)++;
        *(int*)(*byte_code + *ip) = argument;
        *ip += sizeof(int);
    }
    else if(sscanf(line_, "%*s%s", argument_str) == 1 && argument_str[0] == 'r'
                                                    && line_[0] != 'j' && line_[0] != 'c')
    {
        if (false);
        #define DEFREG(name, value)                                              \
        else if(strcasecmp(argument_str, #name) == 0)                            \
        {                                                                        \
            (*byte_code)[*ip] = REG_TYPE;                                        \
            (*ip)++;                                                             \
            (*byte_code)[*ip] = value;                                           \
            (*ip)++;                                                             \
        }
        #include "registers.h"
        #undef DEFREG
    }
    else if(sscanf(line_, "%*s [%d]", &argument) == 1)
    {
        (*byte_code)[*ip] = RAM_TYPE;
        (*ip)++;
        (*byte_code)[*ip] = (char)argument; //so the RAM should not be more than 127!
        (*ip)++;
    }
    else if(sscanf(line_, "%*s%s", argument_str) == 1 && (line_[0] == 'j' || line_[0] == 'c'))
    {
        int flag = 0;
        for(int i = 0; i < MAX_NUMBER_OF_LABELS; i++)
        {
            if(strcmp(labels[i].name, argument_str) == 0)
            {
                *(int*)(*byte_code + *ip) = labels[i].byte_code_adres;
                (*ip) += sizeof(int);

                flag++;
            }
        }
        if(flag == 0)
        {
            *(int*)(*byte_code + *ip) = -1;
            (*ip) += sizeof(int);
        }
    }
    free(argument_str);
}


