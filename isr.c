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
    char message2[] = "pH, LOW";
    char message3[] = "pH, HIGH";
    unsigned char i;
    if (PIR0bits.INTF == 1) //check INT flag
    {
        PIR0bits.INTF = 0; //Clear INT flag
        for (int i = 0; i<10; i++) //start of interrupt tasks
        {
            PORTCbits.RC2 = ~PORTCbits.RC2;
            __delay_ms(300);
        }
        
        lcdSetPos(1,3);
        for (i=0; message1[i]!=0; i++)
        {
            lcdWriteData(message1[i]);
        }
        lcdSetPos(2,3);
        for (i=0; message3[i]!=0; i++)
        {
            lcdWriteData(message3[i]);
        }
        __delay_ms(3000);
        lcdSetPos(1,3);
        for (i=0; message[i]!=0; i++)
        {
            lcdWriteData(message[i]);
        }
        lcdSetPos(2,3);
        for(i=0; message2[i]!=0; i++)
        {
            lcdWriteData(message2[i]);
        }
        
        
        
    }
}

