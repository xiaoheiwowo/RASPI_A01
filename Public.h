#include	"Macro.h"


#ifndef __PUBLIC_H__
#define __PUBLIC_H__


// 全局变量


extern uint CountAvg_Advalue(uint *ADV,uchar Times);

extern int read_bit(uint x, uchar index);
extern uint set_bit(uint * x, uchar index);
extern uint clear_bit(uint * x, uchar index);

#endif

