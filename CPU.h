#ifndef CPU_CPU_H
#define CPU_CPU_H

#include "stack.h"

class CPU
{
    data_t canary1;
    data_t hash_ref;
    data_t hash_new;
    data_t canary2;

    void Cpu();


};


#endif //CPU_CPU_H
