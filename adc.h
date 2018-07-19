#ifndef ADC_H
#define	ADC_H

#include <xc.h> 
#include <stdint.h>

void adc_init(void);
void adc_calibrate(void);

extern uint8_t fvr_val;
extern const uint8_t mah[];

#endif	/* ADC_H */
