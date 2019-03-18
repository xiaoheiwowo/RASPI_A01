/* 
 * File:   P33EV_DMASPI.c
 * Author: liupengyu
 *
 * Created on 2018年7月25日, 上午11:18
 */

#include <stdio.h>
#include <stdlib.h>
#include <xc.h>

#include "Macro.h"
#include "Global.h"
#include "P33EV_Function.h"
#include "P33EV_DMASPI.h"
#include "P33EV_Port.h"
#include "P33EV_ADC.h"
#include "P33EV_Timer.h"
//#include "P33EV_Interrupt.h"

/*
 * 
 */

uint dma_rx_data;

void dma0_init() {
    // 发送通道
    DMA0CONbits.AMODE = 0b00; //带后递增的寄存器间接寻址模式
    DMA0CONbits.MODE = 0b01; //单数据块，禁止乒乓模式
    DMA0CONbits.DIR = 1; //由RAM到外设  
    DMA0CONbits.HALF = 0; //发送全部数据后产生中断
    DMA0CONbits.SIZE = 0; //字传输
    DMA0CONbits.NULLW = 0; //不使用空数据写入功能

    DMA0REQbits.IRQSEL = 0x0A; //SPI1传输完成触发DMA
    _DMA0IF = 0;
    _DMA0IE = 1;    
}

void dma0_start(uint buffer[], uint length) {
    /* 启动一次DMA传输 */
    DMA0CONbits.CHEN = 0;
    dma_sending_mark = 1;
    DMA0STAL = (uint)buffer;
    DMA0STAH = 0x0000;
    
    DMA0PAD = (uint) &SPI1BUF;
    DMA0CNT = length - 1;
    
    IFS0bits.DMA0IF = 0;
    IEC0bits.DMA0IE = 1;
    DMA0CONbits.CHEN = 1;
    // Force First Word After Enabling SPI
    DMA0REQbits.FORCE = 1;
    while (DMA0REQbits.FORCE == 1);
}

void dma0_int_enable() {
    _DMA0IE = 1;
}

void dma0_int_disable() {
    _DMA0IE = 0;
}


void dma1_init() {
    // 接收通道
    DMA1CONbits.AMODE = 0b01; //不带后递增的寄存器间接寻址模式
    DMA1CONbits.MODE = 0b00; //连续数据块模式，禁止乒乓模式
    DMA1CONbits.DIR = 0; //外设到ram  
    DMA1CONbits.HALF = 0; //发送全部数据后产生中断
    DMA1CONbits.SIZE = 0; //字传输
    DMA1CONbits.NULLW = 0; //不使用空数据写入功能

    DMA1REQbits.IRQSEL = 0x0A; //SPI1传输完成触发DMA

    DMA1STAL = (uint) & dma_rx_data;
    DMA1STAH = 0x0000;

    DMA1PAD = (uint) & SPI1BUF;
    DMA1CNT = 0;
    
    _DMA1IF = 0;
    _DMA1IE = 1;
    
    DMA1CONbits.CHEN = 1;

}

void __attribute__((__interrupt__, no_auto_psv)) _DMA0Interrupt(void) {
    dma_sending_mark = 0;
    DMA0CONbits.CHEN = 0;
    _DMA0IF = 0;
}

void __attribute__((interrupt, no_auto_psv)) _DMA1Interrupt(void) {
    spi_rx_buf = dma_rx_data;
    spi_if = 1;
    IFS0bits.DMA1IF = 0; // Clear the DMA0 Interrupt Flag
}