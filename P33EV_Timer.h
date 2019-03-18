#include "Macro.h"

#ifndef __P33EV_Timer_H__
#define __P33EV_Timer_H__
    
#define TxCKPS_1		1				//分频比为1
#define TxCKPS_8		8				//分频比为8
#define TxCKPS_64		64				//分频比为64
#define TxCKPS_256		256				//分频比为256

extern uint Fp;        //外设时钟60MHz

extern uint TxCKPS[5]; //保存定时器的

extern void timer1_init(uint TxCKPS); //初始化定时器1
extern void timer1_start(unsigned long X_us); //定时器
extern void timer1_stop(); //关闭TMR1

extern void timer2_32_init();
extern void timer2_32_start(unsigned long X_us);
extern void timer2_32_stop();

extern void timer3_init();
extern void timer3_start(unsigned long X_us);
extern void timer3_stop(); 


#endif