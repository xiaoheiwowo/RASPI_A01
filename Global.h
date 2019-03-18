/* Microchip Technology Inc. and its subsidiaries.  You may use this software 
 * and any derivatives exclusively with Microchip products. 
 * 
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS".  NO WARRANTIES, WHETHER 
 * EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED 
 * WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A 
 * PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION 
 * WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION. 
 *
 * IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
 * INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
 * WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS 
 * BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE 
 * FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS 
 * IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF 
 * ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE 
 * TERMS. 
 */

/* ——————————————————————————————
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 * ——————————————————————————————*/

// This is a guard condition so that contents of this file are not included
// more than once.  
#include "Macro.h"

#ifndef __GLOBAL_H__
#define	__GLOBAL_H__

// 缓存区结构
typedef struct {
    uint buf[1000];
    // limit是数组元素个数的限制值，而不是索引的限制值
    uint limit;
    // p=最新数据索引值加1
    uint p;
    // uchar full_mark;
    // uchar busy_mark;
    // uchar dma_using;
} Buffer;

extern uchar cmd_byte, par_byte;
extern Buffer BufferA;
//extern Buffer BufferB;
extern Buffer BufferC;

extern uchar ad_mode; // AD 采样模式 0 连续模式 1 查询有限点 2 中断有限点
extern uchar ad_ch_con; // AD 通道控制 每一位为一个通道的开关 1 开 0 关
extern uchar ad_ch_num; // AD 打开的通道数量
extern uchar finish_mark; // 有限点采样完成标志位 1 完成
extern uint samp_number; // 有限点采样点数
extern uchar samp_interval; // 采样时间间隔

extern uchar spi_if; // spi接收标志
extern uint spi_tx_buf; // spi 发送buf
extern uint spi_rx_buf; // spi 接收buf
extern uchar error_code; // 故障码
extern uchar t1_if; //t1中断标志位
extern uchar dma_sending_mark; //dma正在发送

extern void global_var_init();

#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */

    // TODO If C++ is being used, regular C code needs function names to have C 
    // linkage so the functions can be used by the c code. 

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* XC_HEADER_TEMPLATE_H */

