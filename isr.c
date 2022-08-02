/*
 * File:   isr.c
 * Author: boogy
 *
 * Created on 18 July, 2022, 3:51 PM
 */


#include <xc.h>
#include "config.h"

void lcdWriteData(char); 
void lcdSetPos(unsigned char row,unsigned char col);


void __interrupt() isr(void) {
    char message[] = "WASTE, LOW";
    char message1[] = "WASTE, HIGH";
    
    unsigned char i;
    if (PIR0bits.INTF == 1)
    {
        PIR0bits.INTF = 0;
        for (int i = 0; i<10; i++)
        {
            PORTCbits.RC2 = ~PORTCbits.RC2;
            __delay_ms(300);
        }
        //__delay_ms(500);
        lcdSetPos(1,3);
        for (i=0; message1[i]!=0; i++)
        {
            lcdWriteData(message1[i]);
        }
        __delay_ms(1000);
        lcdSetPos(1,3);
        for (i=0; message[i]!=0; i++)
        {
            lcdWriteData(message[i]);
        }
        
        
    }
}

