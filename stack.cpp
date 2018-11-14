//#define class struct
//#define private public
#include "stack.h"
#include <stdio.h>
#include <stdlib.h>
#include <cmath>

#define HASH
#ifdef  HASH
#define _hash_( hash_kind ) if(1) (this->hash_kind) = this->Hash_Refresh()
#else
#define _hash_( hash_kind ) if(0) (this->hash_kind) = this->Hash_Refresh()
#endif


Stack::Stack():
    canary1(CAN1),
    canary2(CAN2),
    capacity(0),
    data(nullptr),
    size(0)
{
    _hash_(hash_ref);
    _hash_(hash_new);
}

#define MAX_CAPACITY 1000

Stack::Stack(size_t capacity_): canary1(CAN1), canary2(CAN2),
                                capacity(capacity_), size(0)
{
    if(capacity_ >= MAX_CAPACITY)
    {
        Test(STACKOVERFLOW);
    }
    this->data = (data_t *) calloc(this->capacity, sizeof(data_t));
    _hash_(hash_ref);
    _hash_(hash_new);
    Test(this->StackOK());
}

Stack::~Stack()
{
    Test(this->StackOK());

    Clean();
    free(this->data);
    this->data = nullptr;
    this->capacity = 0;
    this->size = 0;
}

error_stack Stack::Push (data_t value_)
{
    Test(this->StackOK());
    //printf("FFFF");
    if(this->size == this->capacity)
    {
        //printf("FFFF  ");
        this->Realloc();
    }
    this->data[this->size] = value_;
    (this->size)++;

    _hash_(hash_ref);
    _hash_(hash_new);

    Test(this->StackOK());
    return verificator.last_error;
}

//----------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------POP-------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------

/**
 * @brief function is poping
 * @version 2.0
   @return data_t

 */

data_t Stack::Pop ()
{
    Test(this->StackOK());
    if(this->size <= this->capacity / 2)
    {
        this->Realloc();
    }
    if(this->size == 0)
    {
        //printf("1AAA\n");
        Test(STACKUNDERFLOW);
        return NAN;
    }
    //printf("AAA\n");
    this->size --;
    data_t element_ = this->data[this->size];
    this->data[this->size] = 0;

    _hash_(hash_ref);
    _hash_(hash_new);
    Test(this->StackOK());
    return element_;
}


//----------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------REALLOC-------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------

/**
 * @brief function is empting stack: stack->size = 0;
 * @version 2.0
   @return error_stack test_err.last_error

 * This function is empting stack: stack->size = 0;
 */


#define MULTI_REALLOC 2
#define DIVIDE_REALLOC 0.75


error_stack Stack::Realloc()
{
    Test(this->StackOK());
    if(this->size == this->capacity)
    {
        if(this->capacity >= MAX_CAPACITY)
        {
            Test(STACKOVERFLOW);
            //exit(-1);
            return STACKOVERFLOW;
        }
        else if(this->capacity * MULTI_REALLOC >= MAX_CAPACITY)
        {
            this->data  = (data_t*) realloc (this->data,
                                             MAX_CAPACITY * sizeof (data_t));
            this->capacity = MAX_CAPACITY;
            //verificator.print_file("FFFFFFFFFFFF\n\n");
        }
        else
        {
            //printf("7wwwwwwwwww  ");
            //verificator.print_file("FFFFFFFFFFFF\n\n");

            this->data  = (data_t*) realloc (this->data,
                                         MULTI_REALLOC * this->capacity * sizeof (data_t));
            this->capacity = MULTI_REALLOC * this->capacity;
        }
    }
    else if(this->size <= this->capacity / 2)
    {
        this->data  = (data_t*) realloc (this->data,
                                         (size_t) (DIVIDE_REALLOC * this->capacity) * sizeof (data_t));
        this->capacity = (size_t) (this->capacity * DIVIDE_REALLOC);
        //printf("%d \n", this->capacity);
    }

    Test(this->StackOK());
    return verificator.last_error;

}

#undef MULTI_REALLOC
#undef DIVIDE_REALLOC
#undef MAX_CAPACITY

//----------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------STACK_OK------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------

/**
 * @brief function is cheking our stack
 * @version 1.0
 * @return error_stack test_err.last_error

 * This function cheking if there some errors from "stack_enum.h"
 */

error_stack Stack::StackOK()
{

    if(this->data == nullptr)
    {
        verificator.last_error = BAD_DATA_PTR;
    }
    if(this->canary1 != CAN1)
    {
        verificator.last_error = LEFT_CAN_KILLED;
    }
    if(this->canary2 != CAN2)
    {
        verificator.last_error = RIGHT_CAN_KILLED;
    }
    if(this->size < 0)
    {
        verificator.last_error = BAD_SIZE;
    }
    if(this->capacity < 0)
    {
        verificator.last_error = BAD_CAPACITY;
    }
    if(this->size > this->capacity)
    {
        verificator.last_error = SIZ_BIGGER_CAP;
    }
    if(this->hash_new != this->hash_ref)
    {
        verificator.last_error = BAD_HASH;
    }

    return  verificator.last_error;
}

//----------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------TEST--------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------

/**
 * @brief function is cheking stack
 * @version 2.0
 * @param error_stack error

 * This function cheking if stack was broken: get code of error from StackOK() or from single testing as OVERFLOW
 */

error_stack Stack::Test(error_stack error)
{
    verificator.last_error = error;
    //printf("BBBBB\n");

    if(verificator.last_error != NO_ERR)
    {
        //printf("BBBBB\n");
        verificator.PrintLog();
    }
    return verificator.last_error;
}

//----------------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------DUMP-------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------

/**
 * @brief function is printing data in file "print_stack.txt"
 * @version 2.0
 * @return error_stack test_err.last_error

 * This function cheking if file was not opened
 */

error_stack Stack::Dump()
{
    Test(this->StackOK());
    //printf("RRRR ");
    this->verificator.print_file("\n\n--------------------------------------------------------------------\n");
    this->verificator.print_file("Stack : [%p]\n", this);
    this->verificator.print_file("capacity = %zu\n", this->capacity);
    this->verificator.print_file("size = %zu\n", this->size);
    this->verificator.print_file("data: [%p]\n", this->data);
    for(size_t i = 0; i < this->size; i++)
    {
        this->verificator.print_file("\treal:  data[%d] = %d\n", i, this->data[i]);
    }
    for(size_t i = this->size; i < this->capacity; i++)
    {
        this->verificator.print_file("\tempty: data[%d] = %d\n", i, this->data[i]);
    }
    this->verificator.print_file("--------------------------------------------------------------------\n");

    Test(this->StackOK());
    return this->verificator.last_error;
}

//----------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------CLEAN---------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------

/**
 * @brief function is empting stack: stack->size = 0;
 * @version 2.0
   @return error_stack test_err.last_error

 * This function is empting stack: stack->size = 0;
 */

error_stack Stack::Clean()
{
    Test(this->StackOK());
    while (this->size > 0)
    {
        this->data[this->size - 1] = 0;
        this->size--;
    }

    _hash_(hash_ref);
    //printf("%d\n", hash_new);
    //printf("%d\n", hash_ref);
    _hash_(hash_new);
    Test(this->StackOK());
    //printf("FFFF\n");
    return verificator.last_error;
}

//----------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------SIZE----------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------

/**
 * @brief function is checking stack->size
 * @version 2.0
   @return size_t stack->size

 * This function is checking stack->size
 */

size_t Stack::Size ()
{
    Test(this->StackOK());
    this->hash_new = this->Hash_Refresh();
    return this->size;
}

//----------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------CAPACITY------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------

/**
 * @brief function is checking stack->capacity
 * @version 2.0
   @return size_t stack->capacity

 * This function is checking stack->capacity
 */

size_t Stack::Capacity ()
{
    Test(this->StackOK());
    return this->capacity;
}

//----------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------IS_EMPTY------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------

/**
 * @brief function is checking whether the stack is empty
 * @version 2.0
   @return bool

 * This function is checking whether the stack is empty: 0 == this->size
 */

bool Stack::IsEmpty ()
{
    Test(this->StackOK());
    return 0 == this->size;
}

//----------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------ISFULL--------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------

/**
 * @brief function is checking whether the stack is full
 * @version 2.0
   @return bool

 * This function is checking whether the stack is full: this->capacity == this->size
 */

bool Stack::IsFull ()
{
    Test(this->StackOK());
    return this->capacity == this->size;
}

//----------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------COPY----------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------

/**
 * @brief function is copying new stack with all it's flields
 * @version 2.0
 * @return Stack* stk_copy

 * This function is copying new stack with all it's flields
 */

Stack* Stack::Copy ()
{
    Test(this->StackOK());

    auto stk_copy = new Stack(this->capacity);
    stk_copy->size = this->size;

    for (size_t i = 0; i < this->size ; i++)
    {
        stk_copy->data[i] = this->data[i];
    }
    stk_copy->canary1 = CAN1;
    stk_copy->canary2 = CAN2;
    stk_copy->hash_ref = this->Hash_Refresh();
    stk_copy->hash_new= this->Hash_Refresh();

    Test(this->StackOK());
    return stk_copy;
}


//----------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------HASH_REFRESH--------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------

/**
 * @brief function is counting hash_sum
 * @version 2.0
 * @return data_t hash

 * This function is creating hash_sum for the safety of the stack
 */


data_t Stack::Hash_Refresh()
{

    data_t hash = canary1 / canary2 + 777;
    for (size_t i = 0; i < this->size; i++)
    {
        hash += this->data[i] * i;
    }
    return hash;
}
