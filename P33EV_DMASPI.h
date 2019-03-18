#ifndef __P33EV_DMASPI_H__
#define __P33EV_DMASPI_H__

#define DMACS0  LATBbits.LATB4

extern void dmaspi_init();
extern void dma0_init();
extern void dma0_start(uint buffer[], uint length);
extern void dma0_int_enable();
extern void dma0_int_disable();
extern void dma1_init();


#endif