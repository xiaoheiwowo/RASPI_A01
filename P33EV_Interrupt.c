/* 
 * File:   P33EV_Interrupt.c
 * Author: liupengyu
 *
 * Created on 2018年6月27日, 上午10:38
 */

#include <stdio.h>
#include <stdlib.h>
#include <xc.h>

#include "Macro.h"
#include "P33EV_Function.h"
#include "P33EV_ADC.h"
#include "P33EV_Port.h"
#include "P33EV_Interrupt.h"


void interrupt_enable() {
    /* Enable level 1-7 interrupts */
    /* No restoring of previous CPU IPL state performed here */
    INTCON2bits.GIE = 1;
    return;
}


void interrupt_disable() {
    /* Disable level 1-7 interrupts */
    /* No saving of current CPU IPL setting performed here */
    INTCON2bits.GIE = 0;
    return;
}


void interrupt_init() {
    /* Interrupt nesting enabled here */
    INTCON1bits.NSTDIS = 1; //0 = 使能中断嵌套
    
    /* 设置中断等级 */
    _IPL = 4; // CPU中断优先级状态位
    _SPI1IP = 3;
    _T1IP = 5;
    _T3IP = 3;
    _AD1IP = 3;
    _DMA0IP = 6;
    _SPI1EIP = 4;
    _DMA1IP = 6;
    return;
}


//中断函数的新声明方法
//void __interrupt(auto_psv,irq(52)) _T1Interrupt(void){}

//__interrupt()的参数说明
//save(symbol - list)
//在进入中断时保存并在退出中断时恢复所列的符号 （XC16）
//irq(irqid)
//指定与该中断关联的中断向量 （XC16）
//altirq(altirqid)
//指定与该中断关联的备用中断向量 （XC16）
//preprologue(asm)
//指定需要在任何编译器生成的中断代码之前执行的汇编代码 （XC16）
//shadow
//允许 ISR 利用影子寄存器进行现场切换 （XC16）
//auto_psv
//ISR 将设置 PSVPAG 寄存器，并在退出时恢复它 （XC16）
//no_auto_psv
//ISR 不会设置 PSVPAG 寄存器 （XC16）

