#define CUR_VERSION 20
#define POP         cpu.stk->Pop()
#define ip1         byte_code[ip + 1]
#define ip2         byte_code[ip + 2]
#define ip1___      *(int*)(byte_code + ip + 1)
#define ip2___      *(int*)(byte_code + ip + 2)
#define PUSH        cpu.stk->Push
#define DUMP        Cpu_Dump(cpu, cpu.file_dump)
#define OPR(str)    { int a = POP; int b = POP; PUSH(a str b); ip += 1; DUMP;                    }
#define IF(str)     { int a = POP; int b = POP; if(a str b){ip = ip1___;} else{ip+=5;} DUMP;     }
#define IN          {  int res; scanf("%d", &res); PUSH(res); ip += 1; DUMP;                     }
#define OUT         {  printf("%d\n", POP); ip += 1; DUMP;                                       }
#define EXT         {  exit(1);                                                                  }
#define END         {  ip++; DUMP;                                                               }
#define JMP         {  ip = *(int*)(byte_code + ip + 1);                                         }
#define CALL        {  cpu.stk_call->Push(ip); ip = ip1___;                                      }
#define RET         {  ip = cpu.stk_call->Pop() + 5;                                             }
#define SQR         {  int a = POP; cpu.stk->Push(sqrt(a)); ip += 1; DUMP;                       }
#define MEOW        { system("feh kitten.jpg"); ip++;                                            }

DEFCMD( push,   101,  1, {  if(ip1 == VAL_TYPE)       {PUSH(ip2___);        ip += 6; }
                            else if(ip1 == REG_TYPE)  {PUSH(cpu.REGS[ip2]); ip += 3; }
                            else if(ip1 == RAM_TYPE)  {PUSH(cpu.RAM[ip2]);  ip += 3; }
                            DUMP;
                         })
DEFCMD( pop,    102,  1, {  if(ip1 == REG_TYPE)     {int res = POP; cpu.REGS[ip2] = res; ip += 3;}
                            else if(ip1 == RAM_TYPE){int res = POP; cpu.RAM [ip2] = res; ip += 3;}
                            DUMP;
                        })
DEFCMD( start,  99,    0, DUMP;         )
DEFCMD( add,    110,   0, OPR(+)        )
DEFCMD( sub,    111,   0, OPR(-)        )
DEFCMD( mul,    112,   0, OPR(*)        )
DEFCMD( divide, 113,   0, OPR(/)        )
DEFCMD( sqr,    114,   0, SQR           )
DEFCMD( in,      80,   0, IN            )
DEFCMD( out,     81,   0, OUT           )
DEFCMD( jmp,     50,   1, JMP           )
DEFCMD( ja,      51,   1, IF( > )       )
DEFCMD( jb,      52,   1, IF( < )       )
DEFCMD( je,      53,   1, IF( == )      )
DEFCMD( jne,     54,   1, IF( != )      )
DEFCMD( jae,     55,   1, IF( >= )      )
DEFCMD( jbe,     56,   1, IF( <= )      )
DEFCMD( call,    70,   1, CALL          )
DEFCMD( ret,     71,   0, RET           )
DEFCMD( ext,     -1,   0, EXT           )
DEFCMD( meow,    33,   0, MEOW          )
DEFCMD( end,      1,   0, END           )


