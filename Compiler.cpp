#include <string.h>

#include "Compiler.h"
#include "enum_cmd.h"

#define TEST this->verificator.Test(verificator.last_error);

void Compiler::Compile(FILE *file_asm)
{
    FILE *compiled = fopen("compiled_code.txt", "w");
    if (!compiled)
    {
        this->verificator.last_error = FILE_ERR;
        TEST
        assert(compiled);
    }
    if (file_asm == nullptr)
    {
        this->verificator.last_error = FILE_ERR;
    }
    assert(file_asm);

    /*long file_size = make_buff.Sizeof_file(file_asm);
    TEST

    char* buff = (char*) calloc ((size_t)file_size + 1, sizeof(* buff));   // +1 for last '\0'
    if(buff == nullptr)
    {
        this->verificator.last_error = BAD_PTR;
        TEST
    }
    assert(buff);

    size_t result = fread(buff, sizeof(char), (size_t) file_size, file_asm);
    fseek(file_asm, 0, SEEK_SET);
    if (result != file_size)
    {
        this->verificator.last_error = FREAD_ERR;
        TEST
    }

    int count_line = make_buff.Count_line(buff, file_size);
    free(buff);
    TEST*/
    int count_line = 16;
    auto cmds = (Command *) calloc((size_t) count_line, sizeof(Command));

    for (int i = 0; i < count_line; i++)
    {
        char buf_for_arg[argument_limit];
        char buf_for_name[name_limit];
        fscanf(file_asm, "%s", buf_for_name);
        #define DEFCMD(name, number, letters, arguments)\
                if(strncasecmp(buf_for_name, #name, letters) == 0)\
                {\
                    if(letters == 1)\
                        fscanf(file_asm, "%s", buf_for_arg);\
                }

        #include "commands.h"

        #undef DEFCMD
        cmds[i].name = buf_for_name;
        cmds[i].argument = "";


    }


    for(int i = 0; i < count_line; i++)
    {
        //int name = fscanf(file_asm, "%s", cmds[i].name);
        //int arg  = fscanf(file_asm, "%s", cmds[i].argument);
        printf(" %s, %s\n",  cmds[i].name, cmds[i].argument);
    }
    /*for(int i = 0; i < count_line; i++)
    {
        fprintf(compiled, "%s %s\n", cmds[i].name, cmds[i].argument);
    }*/

    /*for(int i = 0; i < count_line; i++)
    {
        char* buf = cmds[i].name;

#define DEFCMD( name, number, letters)\
                if(strncasecmp(buf, #name, letters) == 0)\
                {\
                    fprintf(compiled, "%d %d\n", CMD_##name, buf[letters]);\
                }
#include "commands.h"
#undef DEFCMD

    }*/
    free(cmds);
    fclose(compiled);

}


/*void Compiler::Scaning_commands(String_view* strings, int count_of_lines)
{
    if(!strings)
    {
        this->verificator.last_error = BAD_PTR;
        TEST
        assert(strings);

    }

    FILE* compiled = fopen("compiled_code.txt", "w");
    if(!compiled)
    {
        this->verificator.last_error = FILE_ERR;
        TEST
        assert(compiled);
    }

    for(int i = 0; i < count_of_lines; i++)
    {
        char* buf = strings[i].string;

        #define DEFCMD( name, number, letters)\
                if(strncasecmp(buf, #name, letters) == 0)\
                {\
                    fprintf(compiled, "%d %d\n", CMD_##name, buf[letters]);\
                }
        #include "commands.h"
        #undef DEFCMD

    }

    fclose(compiled);
}*/


/*void Compiler::Compile(FILE *file_asm)
{
    if(file_asm == nullptr)
    {
        this->verificator.last_error = FILE_ERR;
    }
    assert(file_asm);

    long file_size = make_buff.Sizeof_file(file_asm);
    TEST

    char* buff = (char*) calloc ((size_t)file_size + 1, sizeof(* buff));   // +1 for last '\0'
    if(buff == nullptr)
    {
        this->verificator.last_error = BAD_PTR;
        TEST
    }
    assert(buff);

    size_t result = fread(buff, sizeof(char), (size_t) file_size, file_asm);
    fseek(file_asm, 0, SEEK_SET);
    if (result != file_size)
    {
        this->verificator.last_error = FREAD_ERR;
        TEST
    }
    //printf("%d\n", verificator.last_error);
    int count_line = make_buff.Count_line(buff, file_size);
    TEST
    int count_empty = 0;
    String_view* strings = make_buff.Make_buffstr(buff, count_line, file_size, &count_empty);
    if(!strings)
    {
        this->verificator.last_error = BAD_PTR;
        TEST
    }
    assert(strings);
    int count_of_lines = count_line - count_empty;


    this->Scaning_commands(strings, count_of_lines);

    FILE* fout = fopen("read_commands.txt", "w");
    make_buff.Print_text(fout, strings, (count_of_lines));
    fclose(fout);
    TEST
    free(strings);
    free(buff);
}*/




