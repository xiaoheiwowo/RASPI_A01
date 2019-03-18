#include "Macro.h"

#ifndef __P33EV_Function_H__
#define __P33EV_Function_H__

#define T1_us			20000			//定义T1 为20000uS
#define	Tcytimes	Fosc/MHz(4)             //所以定时时间应该/2特别注意 而不是周期，所以应该是FOSC/4

extern  ulong 	Fosc;
extern  ulong 	Fcy;

//extern  uint    CTTimes;

/*  函数  */
extern void osc_init();                                //系统设置
extern void delay_us(uint t_us);
extern void delay_ms(uint t_ms);
extern void led_green_flash(uchar times, uint interval_ms);
extern void led_blue_flash(uchar times, uint interval_ms);

extern void pic_reset();
extern void clear_wdt();




#endif
