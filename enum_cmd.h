#ifndef CPU_ENUM_CMD_H
#define CPU_ENUM_CMD_H

enum commands
{
#define DEFCMD( name, value, arguments, code ) name = (value),
#include "commands.h"
#undef DEFCMD
};

enum registerss
{
#define DEFREG( name, value) name = (value),
#include "registers.h"
#undef DEFREG
};


#endif //CPU_ENUM_CMD_H
