/*****************************************************************************

Copyright: 2019-2020, KLD Tech. Co., Ltd.

File name: P33EV_ADC.h

Description: (用于详细说明此程序文件完成的主要功能，与其他模块或函数的接口，输出值、
        取值范围、含义及参数间的控制、顺序、独立或依赖等关系)
        
        ADC配置为单通道，12位，扫描采样模式

Author: liupengyu

Version: V0.0

Date: 2019-03-18

History: (修改历史记录列表，每条修改记录应包括修改日期、修改者及修改内容简述。)
        2019-03-18 lpy 增加函数。。。
        
*****************************************************************************/
#include "Macro.h"


#ifndef __P33EV_ADC_H__
#define __P33EV_ADC_H__

extern void adc_init();

extern void adc_set_channel(uchar config_byte);

extern void adc_samp_continue();

extern void adc_samp_some();

#endif
