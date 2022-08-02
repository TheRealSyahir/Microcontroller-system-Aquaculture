/*
 * File:   lcd.c
 * Author: boogy
 *
 * Created on 22 July, 2022, 7:35 PM
 */

#include "config.h"
#include <xc.h>

#define LCD_DATA  PORTC               //Port used by LCD
#define LCD_RS    PORTEbits.RE2       //RS signal for LCD
#define LCD_E     PORTEbits.RE1       //E signal for LCD

//function declarations
void initLCD(void);
void lcdWriteCtrl(char);
void lcdWriteData(char);

// Function to initialise LCD
void initLCD()
{
    // Special Sequence a) to d) required for 4-bit interface
    __delay_ms(15);                 // a) 15ms LCD power-up delay
    lcdWriteCtrl(0b00000011);       // b) Function Set (DB4-DB7:8-bit interface)
    __delay_ms(5);                  // c) 5ms delay
    lcdWriteCtrl(0b00000010);       // d) Function Set (DB4-DB7:4-bit interface)
    lcdWriteCtrl(0b00101000);       // Function Set - 4-bit, 2 lines, 5x7
    lcdWriteCtrl(0b00001100);       // Display on, cursor off
    lcdWriteCtrl(0b00000110);       // Entry mode - inc addr, no shift
    lcdWriteCtrl(0b00000001);       // Clear display & home position
}

// Function to write control instruction, 4-bit at a time
void lcdWriteCtrl(char x)
{
    LCD_RS = 0;
    LCD_DATA = x;
    LCD_E = 1;
    __delay_ms(1);
    LCD_E = 0;
    __delay_ms(1);
    LCD_DATA = x<<4;
    LCD_E = 1;
    __delay_ms(1);
    LCD_E = 0;
    __delay_ms(1);
}
// Function to write data, 4-bit at a time
void lcdWriteData(char x)
{
    LCD_RS = 1;
    LCD_DATA = x;
    LCD_E = 1;
    __delay_ms(1);
    LCD_E = 0;
    __delay_ms(1);
    LCD_DATA = x<<4;
    LCD_E = 1;
    __delay_ms(1);
    LCD_E = 0;
    __delay_ms(1);
}

void lcdSetPos(unsigned char row, unsigned char col)
{
    unsigned char ramAddr;
    
    if (row == 1)
        ramAddr = col - 1;
    else 
        ramAddr = (0x40) + (col - 1);
    
    lcdWriteCtrl(ramAddr + 0x80);
}