#ifndef MACKBUFFSTR_MAKEBUFFSTR_H
#define MACKBUFFSTR_MAKEBUFFSTR_H

#include <stdlib.h>


const char**        Text_to_lines       (const char* file_name_, size_t* count_lines);
const char**        Make_buff_line      (const char** lines_, const char* text_, size_t count_line);
long                Sizeof_file         (const char* file_name_);
size_t              Count_line          (const char* text_);
void                Print_text          (const char** lines_, size_t count_line_);


#endif //MACKBUFFSTR_MAKEBUFFSTR_H
