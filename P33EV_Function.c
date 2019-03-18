/* 
 * File:   P33EV_SPI.c
 * Author: liupengyu
 *
 * Created on 2018年7月3日, 上午11:33
 */

#include <xc.h>
#include "Macro.h"
#include "P33EV_Port.h"
#include "P33EV_Function.h"

ulong Fosc;     //系统时钟
ulong Fcy;      //指令周期时钟 =0.5Fosc
ulong FIN;      //输入PLL的时钟频率
uchar M;        //由PLLDIV<8:0>决定
uchar N1, N2;   //Fin 分频系数
//uint  CTTimes;

// 使用带PLL的内部FRC振荡器
// F_OSC =  F_IN * (M / (N1 * N2))
//     N1 = PLLPRE + 2
//     N2 = 2 x(PLLPOST + 1)
//     M = PLLDIV + 2

void osc_init() {
    OSCTUNbits.TUN = 0B000110;            //调整FRC
    CLKDIVbits.PLLPRE = 0;                  //默认0,  N1 = PLLPRE + 2
    CLKDIVbits.DOZEN = 0;                 //0 = 处理器时钟/ 外设时钟频率比强制为1:1
    CLKDIVbits.FRCDIV = 0;                //0 = FRC 1 分频（默认）001 = FRC 2 分频010 = FRC 4 分频XX
    CLKDIVbits.PLLPOST = 0;                 //000 = 输出/2 01 = 输出/4 （默认）10 = 保留 11 = 输出/8
    PLLFBDbits.PLLDIV = 63;                 //M=65,这样Fosc=7370000*65/4
    // Initiate Clock Switch to FRC oscillator with PLL (NOSC=0b001)
    __builtin_write_OSCCONH(0x01);
    __builtin_write_OSCCONL(0x01);
    // Wait for Clock switch to occur
    while (OSCCONbits.COSC != 0b001);
    // Wait for PLL to lock
    while (OSCCONbits.LOCK != 1){};

    N1 = CLKDIVbits.PLLPRE + 2; 
    N2 = 2 * (CLKDIVbits.PLLPOST + 1); 
    M = PLLFBDbits.PLLDIV + 2;
    FIN = 7366536;                          //输入频率为7.37M
    Fosc = FIN * M / (N1 * N2);             //VCO输出频率
    Fcy = Fosc / 2;                         //时钟频率	59.88MHz   TP=16.7ns
//    CTTimes = (uint) (Fcy / MHZ(4));
    delay_ms(50);
}

void delay_us(uint t_us) {
    int i;
    for (i = 0; i < t_us; i++) {
        // __asm__: 调用汇编指令
        // volatile：阻止 asm 指令被删除、明显移动或合并
        // repeat #59:执行下一条语句60次，占用1指令周期
        // nop : 什么都不干，占用1指令周期
        __asm__ volatile ("repeat #59");//不应该是58？
        __asm__ volatile ("nop");
    }
}

void delay_ms(uint t_ms) {
    int i;
    for (i = 0; i < t_ms; i++){
        delay_us(1000);
    }
}

void led_green_flash(uchar flash_times, uint interval_ms){
//    LED闪烁 参数说明
    // times: 次数
    // interval_ms: 闪烁间隔，单位ms
    uchar i;
    for (i = 0; i < flash_times; i++){
        LED_GREEN = 0;
        delay_ms(interval_ms);
        LED_GREEN = 1;
        delay_ms(interval_ms);
    }
}

void led_blue_flash(uchar flash_times, uint interval_ms) {
    /* LED闪烁 参数说明 */
    // times: 次数
    // interval_ms: 闪烁间隔，单位ms
    uchar i;
    for (i = 0; i < flash_times; i++) {
        LED_BLUE = 0;
        delay_ms(interval_ms);
        LED_BLUE = 1;
        delay_ms(interval_ms);
    }
}

void pic_reset() {
    /* 软件主动复位 */
    __asm__ ("RESET");
}

void clear_wdt() {
    __asm__ volatile ("clrwdt");
}
