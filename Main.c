/* 
 * File:   P33EV_SPI.c
 * Author: liupengyu
 *
 * Created on 2018年7月3日, 上午11:33
 */

#include "ConfigBit.h"
#include <xc.h>

#include "Macro.h"
#include "Global.h"
#include "Public.h"
#include "P33EV_Port.h"
#include "P33EV_Function.h"
#include "P33EV_PWM.h"
#include "P33EV_SPI.h"
#include "P33EV_Timer.h"
#include "P33EV_Interrupt.h"
#include "P33EV_ADC.h"
#include "P33EV_DMASPI.h"

// 定义采样模式 ad_mode 
// = 0 (default)
// = 1 连续采样
// = 2 有限点采样，有限点采样分为两种，带中断信号的和查询式的，
// 两种有限点采样在程序上是一样的，区别在于上位机通过何种方式知道数据采集卡完成采样
#define SAMP_CLOSE      0
#define SAMP_CONTINUE   1
#define SAMP_SOME       2


/************* 全局变量定义 *************/
// spi收到的上位机命令，命令字节和参数字节
uchar cmd_byte, par_byte;
// 两个数据缓存区
Buffer BufferA, BufferC;
// 采样模式 0:default，1:连续采样， 2:有限点采样
uchar ad_mode;
// AD通道配置字节，0b00000000 每一位表示一路AD的开关状态
uchar ad_ch_con;
// 打开的AD通道数量
uchar ad_ch_num;
// 采样完成标志位
uchar finish_mark;
// 有限点采样组数
uint samp_number;
// 采样时间间隔 10ms(default)
uchar samp_interval;
// DMA正在传输数据标志位
uchar dma_sending_mark;
// SPI接收标志位
uchar spi_if;
// SPI发送缓存区
uint spi_tx_buf;
// SPI接收缓存区
uint spi_rx_buf;
// 采样定时器标志位
uchar t1_if;
// 异常码 0:default 2:连续采样发生错误
uchar error_code;
/************* 全局变量END *************/

void global_var_init() {
// 初始化全局变量
    cmd_byte = 0xff;
    par_byte = 0xff;
    ad_mode = SAMP_CLOSE;
    // 默认采样间隔 10ms， 默认所有通道打开
    samp_interval = 10;
    ad_ch_con = 0xff;
    ad_ch_num = 8;
    finish_mark = 0;
    samp_number = 0;

    // BufferA.full_mark = 0;
    BufferA.limit = 1000;
    BufferA.p = 0;
    // BufferA.busy_mark = 0;

    // BufferC.full_mark = 0;
    BufferC.limit = 1000;
    BufferC.p = 0;
    // BufferC.busy_mark = 0;

    spi_rx_buf = 0xffff;
    spi_if = 0;
    t1_if = 0;
    error_code = 0;
    dma_sending_mark = 0;
}


void clear_cmd() {
    cmd_byte = 0xff;
    par_byte = 0xff;
}


int main(void) {
//    初始化
    port_init();
    interrupt_init();
    osc_init();
    adc_init();
    pwm1_init();
    pwm2_init();
    pwm3_init();
    pwm4_init();
    spi_init();
    dma0_init();
    dma1_init();
    timer1_init(256);   // Fp = 60MHz  256分频   timer1可定时0~279616us
    led_blue_flash(2, 100);
    global_var_init();
    LED_BLUE = 0; // Power
    
    while (1) {

        clear_wdt();
        clear_cmd();
        /* 接收一次命令 */
        if (spi_if == 1) {
            cmd_byte = spi_rx_buf >> 8;
            par_byte = spi_rx_buf & 0x00FF;
            spi_if = 0;
        }
        /* 采样定时器标志 */
        if (t1_if == 1) {
            t1_if = 0;
            if (ad_mode == SAMP_CONTINUE) {
                adc_samp_continue();
            }
            else if (ad_mode == SAMP_SOME) {
                adc_samp_some();
            }
        }
        /* IO端口复位 */
        if (RESET == 0) {
            pic_reset();
        }

        // 当正在通过SPI收发数据时, 绿色LED亮。
        // !!! ERROR 将SS当作IO端口读取电平状态将导致模拟引脚上的采样数据出错。
        // if (SS == 0) {
        //     LED_GREEN = 0;
        // }
        // else {
        //     LED_GREEN = 1;
        // }
        
        // 命令处理
        switch (cmd_byte) {
            case 0x01:
                // 配置采样通道
                ad_ch_con = par_byte;
                int i;
                ad_ch_num = 0;
                for (i=0; i<8; i++) {
                    if ((ad_ch_con >> i) & 1) {
                        ad_ch_num += 1;
                    }
                }
                adc_set_channel(ad_ch_con);
                break;
            case 0x02:
                // 配置采样间隔
                samp_interval = par_byte;
                break;
            case 0x03:
                // 启动采样
                BufferA.limit = (par_byte + 1) * ad_ch_num;
                GPIO_19 = 0;
                finish_mark = 0;
                ad_mode = SAMP_CONTINUE;
                timer1_start(samp_interval * 1000);
                break;
            case 0x04:
                // 停止采样
                timer1_stop();
                global_var_init();
                break;
            case 0x05:
                // 查询式有限点采样开始
                BufferA.limit = (par_byte + 1) * ad_ch_num;
                GPIO_19 = 0;
                ad_mode = SAMP_SOME;
                timer1_start(samp_interval * 1000);
                break;
            case 0x06:
                // 带中断信号的有限点采样开始
                BufferA.limit = (par_byte + 1) * ad_ch_num;
                GPIO_19 = 0;
                ad_mode = SAMP_SOME;
                timer1_start(samp_interval * 1000);
                break;
            case 0x07:
                // 读取数据缓存区
                dma0_start(BufferC.buf, BufferC.limit);
                GPIO_19 = 0;
                finish_mark = 0;
                break;
                
            case 0x08:
                // 查询采样完成标志位
                SPI1BUF = finish_mark;
                finish_mark = 0;
                break;
            case 0x09:
                // 读取有限点采样数据
                dma0_start(BufferC.buf, BufferC.limit);
                finish_mark = 0;
                GPIO_19 = 0;
                global_var_init();
                break;
            case 0x0A:
                // 模拟输出通道1
                pwm1_output(par_byte);
                break;
            case 0x0B:
                // 模拟输出通道2
                pwm2_output(par_byte);
                break;
            case 0x0C:
                // 模拟输出通道3
                pwm3_output(par_byte);
                break;
            case 0x0D:
                // 模拟输出通道4
                pwm4_output(par_byte);
                break;
            case 0x0E:
                // 配置IO端口
                set_io(par_byte);
                break;
            case 0x0F:
                // 读IO端口
                SPI1BUF = read_io();
                break;
            case 0x10:
                // 写IO端口
                write_io(par_byte);
                break;
            case 0x11:
                // 异常码
                SPI1BUF = error_code;
                error_code = 0;
                break;
                
            case 0xFE:
                // 软件复位 通过SPI发送复位命令
                if (par_byte == 0xFE) {
                    pic_reset();
                }
                led_green_flash(1, 10);
                break;
        }
    }
    return 0;
}

// __xdata char template[20];

/* END LINE */

