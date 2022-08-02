/*
 * File:   adc.c
 * Author: boogy
 *
 * Created on 1 August, 2022, 10:06 AM
 */


#include <xc.h>
#include "config.h"

// Function to initialise the ADC
void initADC(void)
{
    ADREF = 0b00000000; // Set VREF+ and VREF- to VSS and VDD
    ADCLK = 0b00000011; // Set TAD = 2 us
    ADACQ = 0b00000000; // TACQ to be manually inserted
    ADCON0 = 0b10000000; // Enable ADC, single conversion, FOSC clk,
                            // right justified
}

// Function to start ADC conversion and get the results
unsigned char readPot(void)
{
    unsigned char result; // unsigned char - 1 byte = 8bits
    
    ADPCH = 0b00100000;  // Select channel ANE0 for input at RE0 (trimmer)
    
    __delay_us(5);   // Add 5 us TACQ manually
    ADCON0bits.ADGO=1;        // Start conversion
    while (ADCON0bits.ADGO==1);        // Wait for conversion to complete
    
    result = ADRESH & 0b11100000;
    result = result >> 2; //shift the result to the right by 2 bits since we use RA3,4,5.
    
    
    //result = ADRESH*256+ADRESL;       // Mask the lower 5 bits of the ADC result
           // Shift the upper 3 bits to bits 1~3
    
    return result;   // Return the result
 
}