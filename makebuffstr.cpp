#include "makebuffstr.h"
#define NDEBUG

//----------------------------------------------------------------------------------------------------------------------
//------------------------------------------------SIZEOF_FILE-----------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------

/**
 * @brief function is cheking size
 * @version 2.0
 * @param fin

 * This function cheking size of INPUT.txt file
 */

long Make_buff::Sizeof_file(FILE *fin)
{
    verificator.last_error = NO_ERR;
    if(!fin)
    {
        verificator.last_error = FILE_ERR;
    }
    assert(fin);

    long current = ftell(fin);
    fseek(fin, 0, SEEK_END);
    long size = ftell(fin);
    fseek(fin, 0, (int) current);
    verificator.Test(verificator.last_error);
    return size;
}

//----------------------------------------------------------------------------------------------------------------------
//------------------------------------------------COUNT_LINE------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------


/**
 * @brief function is cheking lines
 * @version 2.0
 * @param char* buff
 * @param long file_size
 * @return int count_line
 *
 *  @code
    int count_line = Count_line(buff, file_size);
    if(count_line <= 0)
    {
        exit(5);
    }
 *  @endcode

 * This function is cheking amount of lines  in INPUT.txt file
 */


int Make_buff::Count_line(char *buff, long file_size)
{
    verificator.last_error = NO_ERR;
    if(!buff)
    {
        verificator.last_error = BAD_PTR;
    }
    assert(buff);

    int count_line = 0;

    for (int i = 0; i < file_size; i++)
    {
        if (buff[i] == '\n')
        {
            buff[i] = '\0';
            count_line++;
        }
    }

    buff[file_size] = '\0'; // last line without '\n'! After last line add one more '\0'
    if(file_size != 0)
    {
        count_line++;      // last line without '\n'
    }
    verificator.Test(verificator.last_error);
    return count_line;
}

//----------------------------------------------------------------------------------------------------------------------
//------------------------------------------------MAKE_BUFFSTR----------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------

/**
 * @brief function is making buffer of strings
 * @version 2.0
 * @param char* buff
 * @param long file_size
 * @paramint count_line
 * @param int* count_empty
 * @return Strings* strings
 * @code
        int count_empty = 0;
        Strings* strings = Make_buffstr(buff, count_line, file_size, &count_empty);
        assert(strings);
 * @endcode

 * This function is making an array of structures Strings from char* buff
 */


String_view* Make_buff::Make_buffstr(char* buff, int count_line, long file_size, int* count_empty)
{
    verificator.last_error = NO_ERR;
    if(!count_empty)
    {
        verificator.last_error = BAD_PTR;
    }
    assert(count_empty);
    if(!buff)
    {
        verificator.last_error = BAD_PTR;
    }
    assert(buff);

    auto strings = (String_view*) calloc((size_t) count_line, sizeof(String_view));
    if(!strings)
    {
        verificator.last_error = BAD_PTR;
    }
    assert(strings);

    char* ptrString = buff;                      // pointer that runs around the buff
    int i = 0;
    int cur_position = 0;

    for(int j = 0; j < file_size + 1; j++)           // +1 because the last one is an additional '\0'
    {
        if(buff[j] == '\0')
        {
            strings[i].length = j - cur_position;// count the length of the lines
            if(i == 0)
            {
                strings[i].length++;             // For the first iteration, when calculating a row, we increase the length
            }
            strings[i].string = ptrString;       // We throw a pointer to a line in the current location of the carriage on the buffer
            ptrString = &(buff[j]) + 1;          // move the carriage
            cur_position = j;
            if(strings[i].length == 1)
            {
                (*count_empty)++;                // if the line was empty (only '\0') DO NOT increase the row counter
            }
            else
            {
                i++;                             // increase i to go to the new element of the array of structures
            }
        }
    }
    verificator.Test(verificator.last_error);
    return strings;
}

//----------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------PRINT_TEXT-----------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------

/**
 * @brief Printing the array of structurs
 * @version 2.0
 * @param FILE* file
 * @param Strings* strings
 * @param int count_line
 * @return void
 *
 * This function is printing the array of stucturs Strings
 */
void Make_buff::Print_text(FILE* file, String_view* strings, int count_line)
{
    verificator.last_error = NO_ERR;
    if(!file)
    {
        verificator.last_error = BAD_PTR;
    }
    if(!strings)
    {
        verificator.last_error = BAD_PTR;
    }
    assert(file);
    assert(strings);

    int i = 0;
    for(i = 0; i < count_line; i++)
    {
        fprintf(file, "%s\n", strings[i].string);
    }
    verificator.Test(verificator.last_error);
}