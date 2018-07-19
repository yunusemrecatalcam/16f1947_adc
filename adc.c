#include <xc.h>
#include "adc.h"
#include <stdint.h>

uint8_t fvr_val;

void adc_init(){
    
    TRISAbits.TRISA0 = 1; //RA0 input 
    ANSELAbits.ANSA0 = 1; //RA0 analog channel for adc
    
    
    ADCON1bits.ADNREF = 0; // vss for vref-
    ADCON1bits.ADPREF = 0b00; // vdd for vref+
    ADCON1bits.ADCS   = 0b100;     
    
    ADCON0bits.CHS = 0b00000; //AN0 == RA0 selected for input
    ADCON0bits.ADON =1;
        
    PIE1bits.ADIE = 1; // ad interrupt enable
    
    //////FVR////////
    
    
}

void adc_calibrate(){
    
    PIE1bits.ADIE = 0b0; // ad interrupt disable
    FVRCONbits.FVREN = 0b1; // fvr enabled
    FVRCONbits.ADFVR = 0b10; // 2,048V
    ADCON0bits.CHS = 0b11111; // FVR selected
    while(!FVRCONbits.FVRRDY);
    NOP();NOP();NOP();NOP();NOP();NOP();
    GO_nDONE =1;            // start reading channel
    while(GO_nDONE);        // wait for completion 
    fvr_val = ADRESH;       //save the value
    ADCON0bits.CHS = 0b00000; //AN0 == RA0 selected for ADC input
    PIE1bits.ADIE = 1; // ad interrupt enable
    
    while(!PIR4bits.TX2IF);
    TX2REG = fvr_val;
}
