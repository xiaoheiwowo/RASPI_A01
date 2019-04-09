/* 
 * File:   P33EV_Port.c
 * Author: liupengyu
 *
 * Created on 2018年6月21日, 下午5:34
 */

#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include "Macro.h"
#include "Public.h"
#include "P33EV_Port.h"

void port_init() {
    /*  */
    
//    TRISx：数据方向寄存器
//    PORTx：I / O 端口寄存器
//    LATx：I / O 锁存寄存器
//    ODCx：漏极开路控制寄存器

    /* Set port configuration */
    TRISA = 0x0083; //AN Input RA: 0,1 ; D Input RA7
    TRISB = 0x000E; //AN Input RB: 1,2,3
    TRISC = 0x0007; //AN Input RC: 0,1,2
    
    // SDI input
    TRISAbits.TRISA9 = 1;
    // SS input
    TRISBbits.TRISB0 = 1;
//    TRISCbits.TRISC3 = 1;
    //    AD0 --> AN8
    //    AD1 --> AN7
    //    AD2 --> AN6
    //    AD3 --> AN5
    //    AD4 --> AN4
    //    AD5 --> AN3
    //    AD6 --> AN1
    //    AD7 --> AN0

    ANSELA = 0x0003;
    ANSELB = 0x000E;
    ANSELC = 0x0007;
    
    ODCA = ODCB = ODCC = 0; //=0
    LATA = LATB = LATC = 0; //=0
    
    // LED 
    LED_GREEN = 1;
    LED_BLUE  = 1;
    GPIO_19 = 0;

    // IO端口配置为输入
    IOS_0 = IOS_1 = IOS_2 = IOS_3 = 1;
    
    port_pps();

}

void port_pps(){
    /* 端口映射 */
    
    //clear the bit 6 of OSCCONL ==> Unlock Registers
    __builtin_write_OSCCONL(OSCCON & ~(1 << 6)); 
    
    // PWM:   OC1 ~ OC4
    _RP57R = 16;
    _RP56R = 17;
    _RP55R = 18;
    _RP54R = 19;

    //set the bit 6 of OSCCONL to Lock Registers  
    __builtin_write_OSCCONL(OSCCON | (1 << 6)); 
}


void set_io(uchar config) {
    
    IOS_0 = read_bit(config, 0);
    IOS_1 = read_bit(config, 1);
    IOS_2 = read_bit(config, 2);
    IOS_3 = read_bit(config, 3);
    
}

uchar read_io() {
    return IN_0 << 0 | IN_1 << 1 | IN_2 << 2 | IN_3 << 3;
}

void write_io(uchar parameter) {
    // 选择通道，只对输出端口进行操作
    if ((parameter & 0x0F) == 0) {
        if ((IOS_0 == 0) && ((parameter & 0xF0) >> 4) > 0 ) {
            OUT_0 = 1;
        } else OUT_0 = 0;
    }
    else if ((parameter & 0x0F) == 1) {
        if ((IOS_1 == 0) && ((parameter & 0xF0) >> 4) > 0) {
            OUT_1 = 1;
        } else OUT_1 = 0;
    }
    else if ((parameter & 0x0F) == 2) {
        if ((IOS_2 == 0) && ((parameter & 0xF0) >> 4) > 0) {
            OUT_2 = 1;
        } else OUT_2 = 0;
    }
    else if ((parameter & 0x0F) == 3) {
        if ((IOS_3 == 0) && ((parameter & 0xF0) >> 4) > 0) {
            OUT_3 = 1;
        } else OUT_3 = 0;
    }
//    通过参数字节选择要设置的IO口和电平状态。参数字节的16进制的第一位表示要选择的 
//    IO口 通道，0：DIO0，1：DIO1，2：DIO2，3：DIO3，其他值无效；第二位表示要写
//    的结果，0：电 平，大于0：高电平。若所选择的IO端口为输入端口，则无效。例如参
//    数字节为0x12，表示要 将DIO2设置为高电平。
}
