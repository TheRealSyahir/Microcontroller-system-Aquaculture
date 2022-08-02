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
    0b11000111, // L
    0b11000000, // O
    0b10001001, // K
    0b10001011, // h
    0b11001111, // I
    0b11111111  // Blank  
};

void disp7seg(void) // Function definition
{
    PORTAbits.RA2 = 0; // Set RA<2:1> = 00
    PORTAbits.RA1 = 0;
    PORTD = segTable[dig0]; // display on rightmost digit of display

    PORTAbits.RA2 = 0; // Set RA<2:1> = 01 
    PORTAbits.RA1 = 1;
    PORTD = segTable[dig1]; // display on rightmost digit of display
}

void lowTemp(void){
    PORTA = 0b00010000;
    dig0 = 0;
    dig1 = 1;
    disp7seg();
}

void normalTemp(void){
    unsigned char i;
    char normTemp[] = "TEMP: NORMAL";
    PORTA = 0b00100000;
    dig0 = 1;
    dig1 = 2;
    disp7seg();
    
    for(i=0; normTemp[i]!=0; i++)
    {
        lcdWriteData(normTemp[i]);
    }
    
}

void highTemp(void){
    PORTA = 0b00001000;
    dig0 = 3;
    dig1 = 4;
    disp7seg();
}

