/* 
 * File:   main.c
 * Author: TrickyNekro
 *
 * Created on July 8, 2019, 11:26 PM
 */

#define _XTAL_FREQ         64000000L

#include <xc.h>
#include <stdio.h>
#include <stdlib.h>



/*
 * 
 */
int main(void)
{
    // Make Port B an output
    TRISB = 0xE7;
    while(1)
    {
        __delay_ms(250);
        LATB |= (1<<3);
        LATB &= ~(1<<4);
        __delay_ms(250);
        LATB &= ~(1<<3);
        LATB |= (1<<4);
    }

}

