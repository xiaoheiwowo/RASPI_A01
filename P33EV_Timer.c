/* 
 * File:   P33EV_Timer.c
 * Author: liupengyu
 *
 * Created on 2018年7月2日, 上午11:56
 */


#include <xc.h>
#include "Macro.h"
#include "Global.h"
#include "P33EV_Timer.h"
#include "P33EV_ADC.h"
#include "P33EV_Port.h"
// #include "p33EV256GM104.h"

uint TxCKPS[5] = {1, 1, 1, 1, 1};   //保存定时器的分频
uint Fp = 60;                       //MHz

void timer1_init(uint Tx_CKPS) {
    // T1 用于AD采样定时
    TxCKPS[0] = Tx_CKPS;        //保存当前分频比
    T1CONbits.TON = 0;          //启停定时器
    T1CONbits.TSIDL = 0;        //空闲模式是否省电
//    T1CONbits.T1ECS = 0B00;   //扩展是时钟：00 辅助时钟 01 T1CK时钟 10 LPRC时钟 11保留

    if (Tx_CKPS == TxCKPS_1) T1CONbits.TCKPS = 0B00; //选择分频系数 【00】==>1:1 
    else if (Tx_CKPS == TxCKPS_8) T1CONbits.TCKPS = 0B01; //选择分频系数 【01】==>1:8
    else if (Tx_CKPS == TxCKPS_64) T1CONbits.TCKPS = 0B10; //选择分频系数 【10】==>1:64
    else if (Tx_CKPS == TxCKPS_256) T1CONbits.TCKPS = 0B11; //选择分频系数 【11】==>1:256

    T1CONbits.TCS = 0; //=【0】选择时钟源：FOSC/2时钟	=【1】 有T1ECS决定
    IPC0bits.T1IP = 6; //中断优先级33
    TMR1 = 0;
    IFS0bits.T1IF = 0; //清除中断标志位
    IEC0bits.T1IE = 1; //允许T1中断
}

//参数说明：X_us : 定时时间单位uS， IsOpen： = True表示需要打开
//定时时间计算方法：
//        指令周期Tp（MHz）, 预分频系数N ，周期寄存器PRx 所赋值为x ，则定时时间为
//        T定时 = Tp*N(X + 1)

//        Fcy = 32MHZ / 2M = 16, T定时 = 1ms = 1000us
//        X = (1000 * Fp / N) - 1

void timer1_start(unsigned long X_us) {
    IFS0bits.T1IF = 0;          //清除标志位
    double Tmp;
    Tmp = X_us * Fp / (double) TxCKPS[0] - 1;
    PR1 = (uint) (Tmp);
    T1CONbits.TON = ON;
}

void timer1_stop() {
    IFS0bits.T1IF = 0;          //清除标志位		
    T1CONbits.TON = OFF;
}

void timer2_32_init() {
    // T2 用于SPI读取指令延时，收到第一字节后等待t2时间 256分频
    TxCKPS[1] = 256; //保存当前分频比
    T2CONbits.TON = 0; //启停定时器
    T3CONbits.TON = 0; //启停定时器
    T2CONbits.TSIDL = 0; //空闲模式是否省电
    T2CONbits.TCKPS = 0B11; //选择分频系数 【10】==>1:64
    T2CONbits.TGATE = 0; // Disable Gated Timer mode
    T2CONbits.T32 = 1;
    T2CONbits.TCS = 0; //=【0】选择时钟源：FOSC/2时钟	=【1】 有T1ECS决定
    TMR3 = 0x00; // Clear 32-bit Timer (msw)
    TMR2 = 0x00; // Clear 32-bit Timer (lsw)
    PR3 = 0x0002; // Load 32-bit period value (msw)
    PR2 = 0x0000; // Load 32-bit period value (lsw)

    IPC2bits.T3IP = 0x01; // Set Timer3 Interrupt Priority Level
    IFS0bits.T3IF = 0; // Clear Timer3 Interrupt Flag
    IEC0bits.T3IE = 1; // Enable Timer3 interrupt
    

    
}

void timer2_32_start(unsigned long X_us) {
    IFS0bits.T3IF = 0; //清除标志位
    double Tmp;
//    Tmp = X_us * Fp;
    Tmp = X_us * Fp / (double) TxCKPS[1] - 1;
    
    PR2 = (ulong) (Tmp) && 0x0000ffff;
    PR3 = (ulong) (Tmp) >> 16;
    TMR3 = 0x00; // Clear 32-bit Timer (msw)
    TMR2 = 0x00; // Clear 32-bit Timer (lsw)
    
    T2CONbits.TON = 1;
}

void timer2_32_stop() {
    IFS0bits.T3IF = 0; //清除标志位		
    T2CONbits.TON = OFF;
}



void __attribute__((__interrupt__, no_auto_psv)) _T1Interrupt(void) {
//    adc_main();
    t1_if = 1;
    _T1IF = 0;
}


void __attribute__((__interrupt__, no_auto_psv)) _T3Interrupt(void) {
    _T3IF = 0;

}
