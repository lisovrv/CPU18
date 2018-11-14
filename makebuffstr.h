#ifndef MACKBUFFSTR_MAKEBUFFSTR_H
#define MACKBUFFSTR_MAKEBUFFSTR_H

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "print_log.h"

typedef struct String_view
{
    char* string; ///< String with data
    int length;   ///< It's length
}String_view;

class Make_buff
{
    Verificator verificator ;
public:
    long            Sizeof_file     (FILE *fin);
    int             Count_line      (char *buff, long file_size);
    String_view*    Make_buffstr    (char* buff, int count_line, long file_size, int* count_empty);
    void            Print_text      (FILE* file, String_view* strings, int count_line);


};


#endif //MACKBUFFSTR_MAKEBUFFSTR_H
