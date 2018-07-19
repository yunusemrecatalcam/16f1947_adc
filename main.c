#include <xc.h>
#include <stdint.h>
#include "timer.h"
#include "serial.h"
#include "adc.h"

#define _XTAL_FREQ 16000000


void main(void) {
    
    adc_init();
    timer_init();
    Serial_init();
    
    TRISBbits.TRISB2 = 0;
    adc_calibrate();
    while(1){
        CLRWDT();
        GO_nDONE =1;
        
        PORTBbits.RB2 ^= 1;
        __delay_ms(500);
    }
    
    return;
}
