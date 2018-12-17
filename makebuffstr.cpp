#include "makebuffstr.h"
#include <sys/stat.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

const char** Text_to_lines(const char* file_name_, size_t* count_lines)
{
    if(file_name_ == nullptr)
    {
        printf("ptr is null!\n");
    }
    assert(file_name_);
    ssize_t file_size = Sizeof_file(file_name_);
    FILE* file = fopen(file_name_, "r");
    if(file == nullptr)
    {
        printf("ptr is null!\n");
    }
    assert(file);

    const char* text = (const char*) calloc((size_t )file_size, sizeof(const char*));
    size_t result = fread((char*)text, sizeof(char), (size_t) file_size, file);
    if(result != file_size)
    {
        printf("fread failed!\n");
    }
    assert(result == file_size);
    fseek(file, 0, SEEK_SET);
    fclose(file);

    *count_lines = Count_line(text);
    const char** lines = (const char**) calloc(*count_lines, sizeof(const char*));
    if(lines == nullptr)
    {
        printf("ptr is null!\n");
    }
    assert(lines);
    lines = Make_buff_line(lines, text, *count_lines);
    return lines;
}

const char** Make_buff_line(const char** lines_, const char* text_, size_t count_line)
{
    if(lines_ == nullptr)
    {
        printf("ptr is null!\n");
    }
    assert(lines_);
    if(text_ == nullptr)
    {
        printf("ptr is null!\n");
    }
    assert(text_);
    char* cur = (char*) text_;
    for(int i = 0; i < count_line; i++)
    {
        char* tmp  = strchr(cur, '\0');
        if(tmp == nullptr)
        {
            break;
        }
        lines_[i] = cur;
        cur = tmp + 1;
    }
    return lines_;
}

void Print_text(const char** lines_, size_t count_line_)
{
    if(lines_ == nullptr)
    {
        printf("ptr is null!\n");
    }
    assert(lines_);
    for(int i = 0; i < count_line_; i++)
    {
        printf("%s\n", lines_[i]);
    }
    printf("\n");
}


size_t Count_line(const char* text_)
{
    if(text_ == nullptr)
    {
        printf("ptr is null!\n");
    }
    assert(text_);
    size_t count_line = 0;
    char* cur = (char*) text_;

    while(cur != nullptr)
    {
        char* tmp  = strchr(cur, '\n');
        if(tmp == nullptr)
        {
            break;
        }
        tmp[0] = '\0';
        cur = tmp + 1;
        count_line++;
    }
    count_line++; //for the last line without '\n'
    return count_line;
}

ssize_t Sizeof_file(const char* file_name_)
{
    if(file_name_ == nullptr)
    {
        printf("ptr is null!\n");
    }
    assert(file_name_);
    struct stat statistics;
    stat(file_name_, &statistics);
    return statistics.st_size;
}