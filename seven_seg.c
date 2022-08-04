/*
 * File:   seven_seg.c
 * Author: boogy
 *
 * Created on 1 August, 2022, 10:04 AM
 */


#include <xc.h>
#include "config.h"

//Nagul

//function declarations
void initLCD(void);
void lcdWriteData(char);

extern unsigned char dig1, dig0; // removed dig2, dig3

// The keyword, const will locate the initialised array in the program
// flash memory. This enables RAM space to be saved up.
// In addition, the const keyword prevents array values from being
// modify
const unsigned char segTable[7] =
{   
    //0b11000000, // O
    0b10001001, // H
    0b11000000, // N
    0b11000111, // L
    
    0b11111111  // Blank  
};


void disp7seg(void) // Function definition
{
    PORTAbits.RA2 = 0; // Set RA<2:1> = 00
    PORTAbits.RA1 = 0;
    PORTD = segTable[dig0]; // display on rightmost digit of display
    /*
    PORTAbits.RA2 = 0; // Set RA<2:1> = 01 
    PORTAbits.RA1 = 1;
    PORTD = segTable[dig1]; // display on rightmost digit of display
    */
}

void lowTemp(void){
    unsigned int cnt;
    PORTA = 0b00010000;
    dig0 = 2;
    //dig1 = 1;
    disp7seg();
    for (cnt = 0; cnt<500; cnt++)
    {
        SPEAKER = 1;
        __delay_us(100);
        SPEAKER = 0;
        __delay_us(100);
    }
}

void normalTemp(void){
    PORTA = 0b00100000;
    dig0 = 1;
    //dig1 = 2;
    disp7seg();
    
}


void highTemp(void){
    unsigned int cnt;
    PORTA = 0b00001000;
    dig0 = 0;
    //dig1 = 4;
    disp7seg();
    for (cnt = 0; cnt<2000; cnt++)
    {
        SPEAKER = 1;
        __delay_us(250);
        SPEAKER = 0;
        __delay_us(250);
    }
}

