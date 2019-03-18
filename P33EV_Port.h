#ifndef __P33EV_PORT_H__
#define __P33EV_PORT_H__

//#define AORD ANSELAbits.ANSA0
#define IOS_0       TRISBbits.TRISB10
#define IOS_1       TRISBbits.TRISB11
#define IOS_2       TRISBbits.TRISB12
#define IOS_3       TRISBbits.TRISB13

// Digital Input
//#define CS0      PORTBbits.RB0

#define IN_0        PORTBbits.RB10
#define IN_1        PORTBbits.RB11
#define IN_2        PORTBbits.RB12
#define IN_3        PORTBbits.RB13

#define RESET       PORTAbits.RA7
#define SS          PORTBbits.RB0

// Digital Output
#define GPIO_19      LATAbits.LATA10
//#define GPIO_26      LATAbits.LATA7
#define LED_BLUE     LATAbits.LATA8
#define LED_GREEN    LATBbits.LATB4

#define OUT_0        LATBbits.LATB10
#define OUT_1        LATBbits.LATB11
#define OUT_2        LATBbits.LATB12
#define OUT_3        LATBbits.LATB13


//#define SPICS0       LATBbits.LATB0

// Analog Input
#define AD0 8
#define AD1 7
#define AD2 6
#define AD3 5
#define AD4 4
#define AD5 3
#define AD6 1
#define AD7 0

// Analog Output


extern void port_init();
void port_pps();

extern void set_io(uchar config);
extern uchar read_io();
extern void write_io(uchar parameter);

#endif