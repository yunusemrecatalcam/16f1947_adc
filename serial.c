#include "serial.h"
#include <pic16f1947.h>

void Serial_init(){
    TRISGbits.TRISG1=0;
    CM3CON0bits.C3ON=0;
    CPSCON0bits.CPSON =0;
    
    ANSELG = 0x00;
    TRISGbits.TRISG1=0;
    
    TX2STAbits.TXEN = 1;    //enable transmitter
    TX2STAbits.SYNC = 0;    //asynchron communication
    RC2STAbits.SPEN = 1;    //eusart1 enable
    
    TX2STAbits.BRGH    = 0;
    
    BAUD2CONbits.BRG16 = 0;
    //SP2BRGLbits.SPBRGL = 51;
    SP2BRGL = 25;
    //sp
    //BAUD2CONbits.ABDEN =1;        
    //PIE4bits.TX2IE =1;
    
    INTCONbits.GIE =1;
    INTCONbits.PEIE =1;
    
     
}


