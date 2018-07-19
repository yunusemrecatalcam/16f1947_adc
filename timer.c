#include <xc.h>
#include "timer.h"
#include <stdint.h>
#include <math.h>
#include "adc.h"

uint8_t timetick=0;

void timer_init(){
    
    //OSCILLATOR
    OSCCONbits.SCS = 0b11;
    OSCCONbits.IRCF = 0b1111;
    OPTION_REGbits.TMR0CS =0;   //8bit timer
    OPTION_REGbits.PSA =1;  // 1:1 prescaler
    INTCONbits.TMR0IE=1;
    TRISGbits.TRISG2 =0;
    INTCONbits.GIE =1;
    
}
uint8_t result= 0;
float voltage;

void interrupt whatifiliall(void){
    if(INTCONbits.TMR0IF){
        INTCONbits.TMR0IF =0;
        timetick++;
        LATBbits.LATB2 ^= 1;
    }
    
    if(PIR1bits.ADIF){
        PIR1bits.ADIF = 0;
        LATGbits.LATG2 ^= 1;
        
        result = ADRESH;
        while(!PIR4bits.TX2IF);
        TX2REG = result;
        
        if(result <103)
            result = 103;
        if(result >140)
            result = 140;
        
        while(!PIR4bits.TX2IF);
        TX2REG = mah[result-103];
        /*voltage = (result*1.000/fvr_val*1.000)* 2.048;
        
        while(!PIR4bits.TX2IF);
        TX2REG = (uint8_t) voltage;
        
        while(!PIR4bits.TX2IF);
        TX2REG = (uint8_t) fmod((voltage*100),100);*/
            
    }
}
