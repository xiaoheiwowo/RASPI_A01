/* 
 * File:   P33EV_SPI.c
 * Author: liupengyu
 *
 * Created on 2018年7月3日, 上午11:33
 */

#include <stdio.h>
#include <xc.h>
#include "Macro.h"
#include "P33EV_SPI.h"

/* 不带增强缓冲区的从模式 
 * 使用4个引脚
 * 使用SPI需要将引脚对应的ANSExbits置为0；并且SDI引脚的TRISxbits置为1,即数字输入端口；
 */

/*
    从模式设置步骤：
    请使用以下步骤将 SPIx 模块设置为从工作模式：
    1. 将 SPIxBUF 寄存器清零。
    2. 如果使用中断，需配置中断控制器：
        a) 将相应 IFSx 寄存器中的 SPIx 中断标志状态位 （SPIxIF）清零。
        b) 将相应 IECx 寄存器中的 SPIx 事件中断允许位 （SPIxIE）置 1。
        c) 通过写相应 IPCx 寄存器中的 SPIx 事件中断优先级位（SPIxIP）来设置中断优先级。
    3. 配置 SPIxCON1 寄存器：
        a) 将主模式使能位 （MSTEN）清零 （SPIxCON1<5> = 0）。
        b) 将数据输入采样阶段位 （SMP）清零 （SPIxCON1<9> = 0）。
        c) 如果时钟边沿选择位 （CKE）置 1，则将从选择使能位 （SSEN）置 1
        （SPIxCON1<7> = 1）来使能 SSx 引脚。
    4. 配置 SPIxSTAT 寄存器：
        a) 将接收溢出标志位 （SPIROV）清零 （SPIxSTAT<6> = 0）。
        b) 通过将 SPIx 使能位 （SPIEN）置 1 （SPIxSTAT<15> = 1）使能 SPIx 工作。
*/
void spi_init() {
    
    SPI1BUF = 0;
    IFS0bits.SPI1IF = 0; // Clear the Interrupt flag
    IEC0bits.SPI1IE = 0; // Disable the interrupt
    // SPI1CON1 Register Settings
    SPI1CON1bits.DISSCK = 0; // Internal Serial Clock is enabled
    SPI1CON1bits.DISSDO = 0; // SDOx pin is controlled by the module
    SPI1CON1bits.SSEN = 0;      // enable ss
    SPI1CON1bits.MODE16 = 1; // 1:16bits | 0:8bits
    SPI1CON1bits.SMP = 0; // Input data is sampled at the middle of data output time.

    // CKE：SPIx 时钟边沿选择位 ~CPHA
    // 1 = 串行输出数据在时钟从工作状态转变为空闲状态时变化
    // 0 = 串行输出数据在时钟从空闲状态转变为工作状态时变化
    // CKP：时钟极性选择位 CPOL
    // 1 = 空闲状态时时钟信号为高电平；工作状态时为低电平
    // 0 = 空闲状态时时钟信号为低电平；工作状态时为高电平
    SPI1CON1bits.CKE = 0;
    SPI1CON1bits.CKP = 0;
    SPI1CON1bits.MSTEN = 0; // 1 主 0 从
    // 时钟配置
//    SPI1CON1bits.SPRE = 0;
//    SPI1CON1bits.PPRE = 1;
    
    SPI1STATbits.SPIROV = 0; // No Receive Overflow has occurred
    SPI1CON2bits.SPIBEN = 0;
    SPI1STATbits.SPIEN = 1; // Enable SPI module
    // Interrupt Controller Settings
    IFS0bits.SPI1IF = 0; // Clear the Interrupt flag
    IEC0bits.SPI1IE = 1; // Enable the interrupt
    _SPI1EIE = 1;
}


void __attribute__((__interrupt__, no_auto_psv)) _SPI1Interrupt(void) {
    /* Insert ISR Code Here*/
    _SPI1IF = 0;
    // 中断产生后一定要读取SPI1BUF,否则无法再次中断。
}

void __attribute__((__interrupt__, no_auto_psv)) _SPI1ErrInterrupt(void) {
    // 仅使用DMA发送SPI不管接收会导致溢出下面的标志位，产生SPI1Error中断
    SPI1STATbits.SPIROV = 0;
    _SPI1EIF = 0;
}
