/* 
 * File:   main.c
 * Author: El. Pro @ TrickyNekro
 *
 * Created on July 8, 2019, 11:26 PM
 */

#define _XTAL_FREQ         64000000L

#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "configuration_pins.h"

/*
 * 
 */
int main(void)
{

    // Initialize the Pins of the Microcontroller 
    PINS_Direction_Configure_Active();
    // Initialize the Peripheral connections to Pins
    PINS_Peripherals_Configure_Active();
    
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

