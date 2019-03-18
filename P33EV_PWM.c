/* 
 * File:   P33EV_PWM.c
 * Author: liupengyu
 *
 * Created on 2018年6月29日, 下午3:05
 */

#include <xc.h>
#include "Macro.h"
#include "P33EV_PWM.h"



void pwm1_init() {
    
    OC1CON1bits.OCSIDL = 0;             //输出比较x在CPU空闲模式下继续工作
    OC1CON1bits.OCTSEL = 0b111;         //输出比较时钟选位，选择Fp
    OC1CON1bits.ENFLTA = 0;             //=1 使能OCFB故障输入
//    OC1CON1bits.OCFLTA = 0;             //当OCM=0B111 ,该位可用 ，=1 只能硬件清零
    OC1CON1bits.TRIGMODE = 0;           //TRIGSTAT只能由软件清零 =1 则当OCxRS=OCxTMR时自动清零TRIGGSTAT ,或由软件清零
    OC1CON1bits.OCM = 0b110;            //=0b110 属于边沿对齐的PWM / =0B111 属于中心对齐的PWM模式

    OC1CON2bits.FLTMD = 0;              //故障模式保存,消除故障后，直到新的PWM周期 =1 则相应的OCFLTx位由软件清零
    OC1CON2bits.FLTOUT = 0;             //发生故障时PWM输出被驱动为低电平 =1 则被驱动为高电平
    OC1CON2bits.FLTTRIEN = 0;           //发生故障调试不受影响； =1 则强制改为输出
    OC1CON2bits.OCINV = 0;              //输出是否反向 输出反向，则=0 就是停止运动，
    OC1CON2bits.OC32 = 0;               //=0 禁止级联模块操作 =1 则使能
    OC1CON2bits.OCTRIG = 1;             //=0 OCX与SYNCSELx位指定的源同步  =1 用SYNCSELx位指定的源触发OCX
    OC1CON2bits.TRIGSTAT = 0;           //=1 表示定时器源已被出发并运行
    OC1CON2bits.OCTRIS = 0;             //=1 OCX引脚是三态引脚 =0 由外设决定
    OC1CON2bits.SYNCSEL = 0b11111;      //这个设置OC1RS作为同步源
    pwm1_stop();
}

void pwm1_output(uint par_b) {
    ulong temp;
    temp = (ulong)par_b * 5999 / 255;
    OC1RS = 5999;
    OC1R = (uint)temp;
}

void pwm1_stop() {
    OC1RS = 5999;
    OC1R = 0;
}

void pwm2_init() {

    OC2CON1bits.OCSIDL = 0; //输出比较x在CPU空闲模式下继续工作
    OC2CON1bits.OCTSEL = 0b111; //输出比较时钟选位，选择Fp
    OC2CON1bits.ENFLTA = 0; //=1 使能OCFB故障输入
    //    OC1CON1bits.OCFLTA = 0;             //当OCM=0B111 ,该位可用 ，=1 只能硬件清零
    OC2CON1bits.TRIGMODE = 0; //TRIGSTAT只能由软件清零 =1 则当OCxRS=OCxTMR时自动清零TRIGGSTAT ,或由软件清零
    OC2CON1bits.OCM = 0b110; //=0b110 属于边沿对齐的PWM / =0B111 属于中心对齐的PWM模式

    OC2CON2bits.FLTMD = 0; //故障模式保存,消除故障后，直到新的PWM周期 =1 则相应的OCFLTx位由软件清零
    OC2CON2bits.FLTOUT = 0; //发生故障时PWM输出被驱动为低电平 =1 则被驱动为高电平
    OC2CON2bits.FLTTRIEN = 0; //发生故障调试不受影响； =1 则强制改为输出
    OC2CON2bits.OCINV = 0; //输出是否反向 输出反向，则=0 就是停止运动，
    OC2CON2bits.OC32 = 0; //=0 禁止级联模块操作 =1 则使能
    OC2CON2bits.OCTRIG = 1; //=0 OCX与SYNCSELx位指定的源同步  =1 用SYNCSELx位指定的源触发OCX
    OC2CON2bits.TRIGSTAT = 0; //=1 表示定时器源已被出发并运行
    OC2CON2bits.OCTRIS = 0; //=1 OCX引脚是三态引脚 =0 由外设决定
    OC2CON2bits.SYNCSEL = 0b11111; //这个设置OC1RS作为同步源
    pwm2_stop();
}

void pwm2_output(uint par_b) {
    ulong temp;
    temp = (ulong) par_b * 5999 / 255;
    OC2RS = 5999;
    OC2R = (uint) temp;
}

void pwm2_stop() {
    OC2RS = 5999;
    OC2R = 0;
}

void pwm3_init() {

    OC3CON1bits.OCSIDL = 0; //输出比较x在CPU空闲模式下继续工作
    OC3CON1bits.OCTSEL = 0b111; //输出比较时钟选位，选择Fp
    OC3CON1bits.ENFLTA = 0; //=1 使能OCFB故障输入
    //    OC1CON1bits.OCFLTA = 0;             //当OCM=0B111 ,该位可用 ，=1 只能硬件清零
    OC3CON1bits.TRIGMODE = 0; //TRIGSTAT只能由软件清零 =1 则当OCxRS=OCxTMR时自动清零TRIGGSTAT ,或由软件清零
    OC3CON1bits.OCM = 0b110; //=0b110 属于边沿对齐的PWM / =0B111 属于中心对齐的PWM模式

    OC3CON2bits.FLTMD = 0; //故障模式保存,消除故障后，直到新的PWM周期 =1 则相应的OCFLTx位由软件清零
    OC3CON2bits.FLTOUT = 0; //发生故障时PWM输出被驱动为低电平 =1 则被驱动为高电平
    OC3CON2bits.FLTTRIEN = 0; //发生故障调试不受影响； =1 则强制改为输出
    OC3CON2bits.OCINV = 0; //输出是否反向 输出反向，则=0 就是停止运动，
    OC3CON2bits.OC32 = 0; //=0 禁止级联模块操作 =1 则使能
    OC3CON2bits.OCTRIG = 1; //=0 OCX与SYNCSELx位指定的源同步  =1 用SYNCSELx位指定的源触发OCX
    OC3CON2bits.TRIGSTAT = 0; //=1 表示定时器源已被出发并运行
    OC3CON2bits.OCTRIS = 0; //=1 OCX引脚是三态引脚 =0 由外设决定
    OC3CON2bits.SYNCSEL = 0b11111; //这个设置OC1RS作为同步源
    pwm3_stop();
}

void pwm3_output(uint par_b) {
    ulong temp;
    temp = (ulong) par_b * 5999 / 255;
    OC3RS = 5999;
    OC3R = (uint) temp;
}

void pwm3_stop() {
    OC3RS = 5999;
    OC3R = 0;
}

void pwm4_init() {

    OC4CON1bits.OCSIDL = 0; //输出比较x在CPU空闲模式下继续工作
    OC4CON1bits.OCTSEL = 0b111; //输出比较时钟选位，选择Fp
    OC4CON1bits.ENFLTA = 0; //=1 使能OCFB故障输入
    //    OC1CON1bits.OCFLTA = 0;             //当OCM=0B111 ,该位可用 ，=1 只能硬件清零
    OC4CON1bits.TRIGMODE = 0; //TRIGSTAT只能由软件清零 =1 则当OCxRS=OCxTMR时自动清零TRIGGSTAT ,或由软件清零
    OC4CON1bits.OCM = 0b110; //=0b110 属于边沿对齐的PWM / =0B111 属于中心对齐的PWM模式

    OC4CON2bits.FLTMD = 0; //故障模式保存,消除故障后，直到新的PWM周期 =1 则相应的OCFLTx位由软件清零
    OC4CON2bits.FLTOUT = 0; //发生故障时PWM输出被驱动为低电平 =1 则被驱动为高电平
    OC4CON2bits.FLTTRIEN = 0; //发生故障调试不受影响； =1 则强制改为输出
    OC4CON2bits.OCINV = 0; //输出是否反向 输出反向，则=0 就是停止运动，
    OC4CON2bits.OC32 = 0; //=0 禁止级联模块操作 =1 则使能
    OC4CON2bits.OCTRIG = 1; //=0 OCX与SYNCSELx位指定的源同步  =1 用SYNCSELx位指定的源触发OCX
    OC4CON2bits.TRIGSTAT = 0; //=1 表示定时器源已被出发并运行
    OC4CON2bits.OCTRIS = 0; //=1 OCX引脚是三态引脚 =0 由外设决定
    OC4CON2bits.SYNCSEL = 0b11111; //这个设置OC1RS作为同步源
    pwm4_stop();
}

void pwm4_output(uint par_b) {
    ulong temp;
    temp = (ulong) par_b * 5999 / 255;
    OC4RS = 5999;
    OC4R = (uint) temp;
}

void pwm4_stop() {
    OC4RS = 5999;
    OC4R = 0;
}