#include "Macro.h"


#ifndef __P33EV_ADC_H__
#define __P33EV_ADC_H__

extern void adc_init();

extern void adc_set_channel(uchar config_byte);

extern void adc_samp_continue();

extern void adc_samp_some();

#endif
