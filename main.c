/*
 * File:   main.c
 * Author: boogy
 *
 * Created on 18 July, 2022, 2:22 PM
 */


#include <xc.h>
#include "config.h"

#define S2 PORTBbits.RB2  //bryant
unsigned int detSW1(void); //bryant

//Nagul
void initADC(void);
void disp7seg(void);
void lowTemp(void);
void normalTemp(void);
void highTemp(void);
unsigned char readPot(void);
unsigned char dig1, dig0;


//Function declarations
void initSysPins(void);
void initSysDevices(void);
void __interrupt() isr(void);
void initLCD(void);
void lcdWriteData(char); 
void lcdSetPos(unsigned char row,unsigned char col); 

void main(void) {
    initSysPins(); //initialise ports
    initSysDevices();
    initLCD(); //initialise LCD module
    unsigned int pwm_duty_value = 0; //declare var and initialise(bryant)
    detSW1(); //bryant
    PWM6CONbits.EN = 1; //Enable PWM (bryant)
    unsigned int result; // unsigned int - 2 byte = 16bits (Nagul)
     initADC(); //Nagul

    char message[] = "WASTE, LOW";
    char message1[] = "WASTE, HIGH";
    char message2[] = "pH, LOW";
    char message3[] = "pH, HIGH";
    unsigned char i;
    
    lcdSetPos(1,3);
    for (i=0; message[i]!=0; i++)
        {
            lcdWriteData(message[i]);
        }
    lcdSetPos(2,3);
    for (i=0; message2[i]!=0; i++)
    {
        lcdWriteData(message2[i]);
    }
    while(1)
    {
        PORTCbits.RC1 = 1;
        
        PORTBbits.RB0 = 1; //start of bryant main 
        if (detSW1()==1)
        {
            //Increase duty-cycle in steps of 5%
            //When duty is more than 100%, reset to zero
            //Apply new duty-cycle to PWM6DCH and PWM6DCL 
            pwm_duty_value += 25;
            
            if (pwm_duty_value > 500)
            {
                for (int i = 0; i<10; i++)
                {
                    PORTBbits.RB0 = ~PORTBbits.RB0;
                    __delay_ms(200);
                }
                pwm_duty_value = 0;
               
            }
            else if(pwm_duty_value < 50)
            {
               for (int i = 0; i<10; i++)
                {
                    PORTBbits.RB0 = ~PORTBbits.RB0;
                    __delay_ms(200);
                }
            }
            PWM6DCH = pwm_duty_value >> 2;
            PWM6DCL = (pwm_duty_value & 0b00000011) << 6; //end of bryant main
        }
        //Nagul

        //get trimmer value
        result = readPot();
        
        //LOW
        if (result == 0b00000000 || result == 0b00001000 )
            lowTemp();
 
        //NORMAL
        else if (result == 0b00010000 || result == 0b00011000 || result == 0b00100000)
            normalTemp();
        
        //HIGH
        else if (result == 0b00110000 || result == 0b00111000)
            highTemp();  
        
    }
}

void initSysPins(void)
{
    ANSELA = 0; //bryant & nagul
    TRISA = 0b11000000; //bryant & nagul
    ANSELB = 0;
    TRISB = 0b11111110; // RB0 - output(LED5) & RB2(S2) Bryant, Syahir(RB5)S3)
    ANSELC = 0;
    TRISC = 0b00000000; // RC7-RC4 digital output(LCD), RC1 & RC2 output(LEDs)
    ANSELD = 0; //nagul
    TRISD = 0b00000000; //nagul
    ANSELE = 0b00000001;
    TRISE = 0b11111001; // RE2 & RE1 - digital outputs for E,RS LCD(Syahir),RE0 - input
}

void initSysDevices(void)
{
    //Syahir initSysDevices
    INTCONbits.GIE = 0;
    PIR0bits.INTF = 0;
    INTPPS = 0x0D;
    INTCONbits.INTEDG = 1;
    PIE0bits.INTE = 1;
    INTCONbits.GIE = 1;
    
    //Bryant initSysDevices
    CCPTMRS1 = 0b00000100;
    PWM6CON = 0b00000000;
    T2PR = 124;
    PWM6DCH = 0b00000000;
    PWM6DCL = 0b00000000;
    T2CON = 0b11110000;
    T2CLKCON = 0b00000001;
    RA0PPS = 0x0E;
}

//bryant
unsigned int detSW1(void)
{
    unsigned int detect = 0;
    if (S2 == 0)
    {
        __delay_ms(50);
        if (S2 ==0)
        {
            detect=1;
            while (S2 == 0);
        }
    }
    return detect;
}

