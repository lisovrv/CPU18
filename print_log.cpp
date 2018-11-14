#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "stack.h"

#define EXIT
#ifdef EXIT
#define exit( num ) if(1) exit( num )
#else
#define exit( num ) if(0) exit( num )
#endif



Verificator::Verificator()
{
    FILE* print_log = fopen("print_log.txt", "r+" );
    this->verificator = print_log;
    if(this->verificator == nullptr)
    {
        last_error = FILE_ERR;
    }
    else
    {
        last_error = NO_ERR;
    }
}

/*Verificator::Verificator(const char* file_name)
{
    this->verificator = file_name;
    if(this->verificator == nullptr)
    {
        last_error = FILE_ERR;
    }
    else
    {
        last_error = NO_ERR;
    }
}*/

Verificator::~Verificator()
{
    if(fclose(this->verificator) != 0)
    {
        last_error = CLOSE_ERR;
    }
    this->verificator = nullptr;
}

error_stack Verificator::PrintLog()
{
    switch (this->last_error)
    {
        case  BAD_DATA_PTR:
            this->print_file("ERROR: the pointer on this->data is nullptr: YOU CAN'T USE POINTER ANYMORE\n");
            exit(BAD_DATA_PTR);
            return BAD_DATA_PTR;
        case  LEFT_CAN_KILLED:
            this->print_file("ERROR: the canary1 was killed: YOU CAN'T USE STACK ANYMORE\n");
            exit(LEFT_CAN_KILLED);
            return LEFT_CAN_KILLED;
        case  RIGHT_CAN_KILLED:
            this->print_file("ERROR: the canary2 was killed: YOU CAN'T USE STACK ANYMORE\n");
            exit(RIGHT_CAN_KILLED);
            return RIGHT_CAN_KILLED;
        case  BAD_SIZE:
            this->print_file("ERROR: this->size is less than zero: YOU CAN'T USE STACK ANYMORE\n");
            exit(BAD_SIZE);
            return BAD_SIZE;
        case  BAD_CAPACITY:
            this->print_file("ERROR: this->capacity is less than zero: YOU CAN'T USE STACK ANYMORE\n");
            exit(BAD_CAPACITY);
            return BAD_CAPACITY;
        case  SIZ_BIGGER_CAP:
            this->print_file("ERROR: this->size is bigger than this->capacity: YOU CAN'T USE STACK ANYMORE\n");
            exit(SIZ_BIGGER_CAP);
            return SIZ_BIGGER_CAP;
        case  FILE_ERR:
            this->print_file("ERROR: file was not opened: YOU CAN'T USE FILE ANYMORE\n");
            exit(FILE_ERR);
            return FILE_ERR;
        case  CLOSE_ERR:
            this->print_file("ERROR: file was not correctly closed: YOU CAN'T USE FILE ANYMORE\n");
            exit(CLOSE_ERR);
            return CLOSE_ERR;
        case  BAD_PTR:
            this->print_file("ERROR: the pointer is nullptr: YOU CAN'T USE POINTER ANYMORE\n");
            exit(BAD_PTR);
            return BAD_PTR;
        case  BAD_HASH:
            this->print_file("ERROR: the hash was spoilt: YOU CAN'T USE STACK ANYMORE\n");
            exit(BAD_HASH);
            return  BAD_HASH;
        case  STACKOVERFLOW:
            this->print_file("ERROR: stack is overflow: YOU CAN'T USE STACK ANYMORE\n");
            exit(STACKOVERFLOW);
            return STACKOVERFLOW;
        case  STACKUNDERFLOW:
            this->print_file("ERROR: stack is underflow: YOU CAN'T USE STACK ANYMORE\n");
            exit(STACKUNDERFLOW);
            return STACKUNDERFLOW;
        case  FREAD_ERR:
            this->print_file("ERROR: fread return mistake: YOU CAN'T USE file ANYMORE\n");
            exit(FREAD_ERR);
            return FREAD_ERR;
        default:
            return NO_ERR;
    }


}

error_stack Verificator::Test(error_stack error)
{
    this->last_error = error;

    if(this->last_error != NO_ERR)
    {
        this->PrintLog();
    }
    return this->last_error;
}

error_stack Verificator::print_file(const char *fmt, ... )
{
    if(fmt == nullptr)
    {
        this->last_error = BAD_PTR;
    }
    if(this == nullptr)
    {
        this->last_error = BAD_PTR;
    }

    va_list args;
    va_start( args, fmt );
    vfprintf(this->verificator, fmt, args );
    va_end( args );

    return this->last_error;
}



