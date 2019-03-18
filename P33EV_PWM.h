#ifndef __P33EV_PWM_H__
#define __P33EV_PWM_H__

extern void pwm1_init();
extern void pwm1_output(unsigned int par_b);
extern void pwm1_stop();

extern void pwm2_init();
extern void pwm2_output(unsigned int par_b);
extern void pwm2_stop();

extern void pwm3_init();
extern void pwm3_output(unsigned int par_b);
extern void pwm3_stop();

extern void pwm4_init();
extern void pwm4_output(unsigned int par_b);
extern void pwm4_stop();


#endif