/* 
 * File:   P33EV_SPI.c
 * Author: liupengyu
 *
 * Created on 2018年7月3日, 上午11:33
 */

#include <xc.h>

#include "Macro.h"
#include "P33EV_ADC.h"

#include "Global.h"
#include "Public.h"
#include "P33EV_Port.h"
#include "P33EV_Function.h"
#include "P33EV_Interrupt.h"
#include "P33EV_Timer.h"
#include "P33EV_PWM.h"

/* 只有AN0~AN31可以使用扫描,不推荐使用32~63 
 * CH123不能连接到任意引脚*/

// 切换通道时要写入CH0SA的值
const uchar list_CH0SA[8] = {8, 7, 6, 5, 4, 3, 1, 0};

// AD 通道选择数组
//    AD0 --> AN51
//    AD1 --> AN52
//    AD2 --> AN53
//    AD3 --> AN54
//    AD4 --> AN31
//    AD5 --> AN25
//    AD6 --> AN26
//    AD7 --> AN27


void adc_init(){ 
// AD转换的初始化
// 配置为 12 位单通道 8 路扫描模式
// 自动采样，自动转换

    AD1CON1bits.ADON = 0;       //停止ADC
    AD1CON1bits.ADSIDL = 0;     //空闲时停止工作，目的是省电
    AD1CON1bits.ADDMABM = 0;    //ADC DMA
    AD1CON1bits.AD12B = 1;	    //12位模式
    AD1CON1bits.FORM = 0;       //00 无符号绝对十进制右对齐
    AD1CON1bits.SSRCG = 0;      //以0方式对SSRC进行编程
    AD1CON1bits.SSRC = 0B111;   //采样结束后自动转换
    AD1CON1bits.SIMSAM = 0;     //=0一次采样 ，=1 同时采样
    AD1CON1bits.ASAM = 1;       //自动采样
    
    AD1CON2bits.VCFG = 0;	    //00表示内部AVDD   01表示外部VREF+
    AD1CON2bits.CSCNA = 0;	    //=1 扫描输入 则只对CHOSA通道扫描采集  =0 不扫描输入扫描
    AD1CON2bits.SMPI = 7;       //=0 每完成1 次采样/ 转换操作后递增DMA 地址或产生中断
    AD1CON2bits.BUFM = 0;       //=0:	从ADCBUF0 开始填充缓冲区，且在连续中断时按顺序填充每个地址【FIFO模式】
                                //=1:	从第一次产生中断时从ADCBUF0 开始填充缓冲区，产生下一次中断时从AD1BUF(n/2）开始填充【分割缓冲模式】
    
    AD1CON2bits.CSCNA = 1;      // 输入扫描选择位: 1 = 扫描采样MUX A选择的CH0+输入;0 = 不扫描输入
    AD1CON2bits.CHPS = 0;       // 通道选择位: 00 = 转换CH0

    AD1CON3bits.ADRC = 0;	    //1 = ADC 内部RC 时钟 0 = 时钟由系统时钟产生
    AD1CON3bits.ADCS = 5;	    //AD的时钟周期 1TAD=12TP 保证TAD>75ns
    AD1CON3bits.SAMC = 7;	    //自动采样时间位  15*TAD
    AD1CON4bits.ADDMAEN = 0;    //DMA使能=0 禁止DMA

    AD1CHS0bits.CH0NB = 0;	    //采样通道负输入选择为=0 AVSS
    AD1CHS0bits.CH0NA = 0;	    //采样通道负输入选择为=0 AVSS
    
    AD1CSSH = 0x0000;
    AD1CSSL = 0x01FB;           //根据原理图使用的模拟输入端口配置AD1CSSL和AD1CSSH
    
//    AD1CHS0bits.CH0SA = 1;

    IPC3bits.AD1IP = 3;         //置A/D的优先级5
    IFS0bits.AD1IF = 0;         //清A/D中断标志J
    AD1CON1bits.ADON = 1;
}


void adc_set_channel(uchar config_byte) {
// 根据通道配置字节配置采样通道(AD1CSSL)，重新启动AD采样
    AD1CON1bits.ADON = 0;
    _AD1IF = 0;
    int i;
    AD1CSSL = 0;
    for (i=0; i<8; i++) {
        if ((config_byte >> i) & 1) {
            AD1CSSL |= (1 << list_CH0SA[i]);
        }
    }
    AD1CON1bits.ADON = 1;
}

void adc_get_data_from_ADC1BUF(uint ar_adv[]) {
// 将8个通道的采样数据从ADC1BUF中移出到数组
    if (_AD1IF == 1) {
        _IPL = 7;
        ar_adv[0] = ADC1BUF7; 
        ar_adv[1] = ADC1BUF6; 
        ar_adv[2] = ADC1BUF5; 
        ar_adv[3] = ADC1BUF4; 
        ar_adv[4] = ADC1BUF3; 
        ar_adv[5] = ADC1BUF2; 
        ar_adv[6] = ADC1BUF1; 
        ar_adv[7] = ADC1BUF0; 
        _IPL = 4;
        _AD1IF = 0;
        // _DONE = 0;
    }
}

void adc_BufferA_to_BufferC() {
    // 将BufferA中的数据转移到BufferC,用于DMA-SPI发送
    int i;
    for (i = 0; i < BufferA.limit; i++) {
        BufferC.buf[i] = BufferA.buf[i];
    }
    BufferC.limit = BufferA.limit;
    GPIO_19 = 1;
    finish_mark = 1;
}


void adc_samp_continue() {
// 连续采样模式
// 采样所有通道一次并存入对应的数据缓存区 Timer1中断函数的程序
    uint ar_adv[8] = {0};
    adc_get_data_from_ADC1BUF(ar_adv);
    int i;
    for (i = 0; i < 8; i++) {
        // 根据打开的通道保存有效数据
        if ((ad_ch_con >> i) & 1) {
            BufferA.buf[BufferA.p] = ar_adv[i];
            BufferA.p++;
            // 将BufferA复制到BufferC，给出采样完成信号
            if (BufferA.p == BufferA.limit) {
                BufferA.p = 0;
                if (dma_sending_mark == 0) {
                    adc_BufferA_to_BufferC();
                } 
                else {
                    // 若此时DMA还未将所有数据发送完，数据采集卡将停止采样并给出异常码
                    GPIO_19 = 0;
                    finish_mark = 0;
                    timer1_stop();
                    global_var_init();
                    error_code = 2;
                }
                break;
            }
        }
    }
}

void adc_samp_some() {
    uint ar_adv[8];
    adc_get_data_from_ADC1BUF(ar_adv);
    int i;
    for (i = 0; i < 8; i++) {
        if ((ad_ch_con >> i) & 1) {
            BufferA.buf[BufferA.p] = ar_adv[i];
            BufferA.p++;
            // 将BufferA复制到BufferC，给出采样完成信号和标志位，停止采样定时器
            if (BufferA.p == BufferA.limit) {
                BufferA.p = 0;
                adc_BufferA_to_BufferC();
                timer1_stop();
                break;
            }
        }
    }
}
