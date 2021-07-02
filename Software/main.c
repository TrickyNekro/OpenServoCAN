/* 
 * File:   main.c
 * Author: El. Pro @ TrickyNekro
 *
 * Created on July 8, 2019, 11:26 PM
 */

#define _XTAL_FREQ         64000000L
#define C_STEP             5
#define PWM_LIM            1023


#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "configuration_pins.h"
#include "Timer_2.h"
#include "Timer_4.h"
#include "Timer_6.h"
#include "PWM5_Module.h"
#include "PWM6_Module.h"
#include "PWM7_Module.h"
#include "PWM8_Module.h"

/*
 * 
 */
int main(void)
{
    // Initialize the Pins of the Microcontroller 
    PINS_Direction_Configure_Active ( );
    
    // Disable all LED pins
    LATAbits.LATA7 = 1;
    LATAbits.LATA6 = 1;
    LATAbits.LATA5 = 1;
    
    // Initialize the Peripheral connections to Pins
    PINS_Peripherals_Configure_Active ( );
    // Initialize Timer 2
    Timer_2_Configure ( T2CON_CKPS_PRESC_1_2, T2CON_OUTPS_POST_1_1, 
                        T2CKL_CS_F_OSC_DIV_4, TMR2_PERIOD_MAX, 
                        T2RST_RSEL_T2INPPS, T2HLT_MODE_FR_SOFT_GATE, 
                        T2HLT_PSYNC_OFF, T2HLT_CKPOL_RISING, T2HLT_CKSYNC_ON,
                        true, true, false, false );
    // Initialize PWM 5 Module
    PWM_5_Initialize ( CCPTMRS1_P5TSEL_TMR2, true, true );
    PWM_6_Initialize ( CCPTMRS1_P6TSEL_TMR2, true, true );
    PWM_8_Initialize ( CCPTMRS1_P8TSEL_TMR2, true, true );
    
    // Temporary Variables
    int16_t counter_R   = 0;
    int16_t counter_G   = 341;
    int16_t counter_B   = 682;
    bool    increment_R = true;
    bool    increment_G = true;
    bool    increment_B = true;
    
    // Main Loop
    while(1) { 
        
        // Create a ramp
        if ( increment_R ) {
            // Add to the counter
            counter_R += C_STEP;
            // Change the direction if overflow
            if ( counter_R > PWM_LIM ) {
                // Cap the counter value
                counter_R = PWM_LIM;
                // Start decrementing
                increment_R = false;
            }
        }
        else {
            // Subtract from the counter
            counter_R -= C_STEP;
            // Change the direction if overflow
            if ( counter_R < 0 ) {
                // Cap the counter value
                counter_R = 0;
                // Start incrementing
                increment_R = true;
            }
        }
        // Create a ramp
        if ( increment_G ) {
            // Add to the counter
            counter_G += C_STEP;
            // Change the direction if overflow
            if ( counter_G > PWM_LIM ) {
                // Cap the counter value
                counter_G = PWM_LIM;
                // Start decrementing
                increment_G = false;
            }
        }
        else {
            // Subtract from the counter
            counter_G -= C_STEP;
            // Change the direction if overflow
            if ( counter_G < 0 ) {
                // Cap the counter value
                counter_G = 0;
                // Start incrementing
                increment_G = true;
            }
        }
        // Create a ramp
        if ( increment_B ) {
            // Add to the counter
            counter_B += C_STEP;
            // Change the direction if overflow
            if ( counter_B > PWM_LIM ) {
                // Cap the counter value
                counter_B = PWM_LIM;
                // Start decrementing
                increment_B = false;
            }
        }
        else {
            // Subtract from the counter
            counter_B -= C_STEP;
            // Change the direction if overflow
            if ( counter_B < 0 ) {
                // Cap the counter value
                counter_B = 0;
                // Start incrementing
                increment_B = true;
            }
        }
        
        // Load the values to the PWM Module
        PWM_5_Set_Output_No_Cap ( counter_R );
        PWM_6_Set_Output_No_Cap ( counter_B );
        PWM_8_Set_Output_No_Cap ( counter_G );
        // Delay for effect
        __delay_ms ( 10 ); 
    }

}

