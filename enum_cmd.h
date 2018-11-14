#ifndef CPU_ENUM_CMD_H
#define CPU_ENUM_CMD_H

enum commands
{
#define DEFCMD( name, num, letters, arguments) CMD_##name = (num),

#include "commands.h"
    CMD_MAX = 500
#undef DEFCMD

};
#endif //CPU_ENUM_CMD_H
