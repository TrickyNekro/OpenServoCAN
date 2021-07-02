/* 
 * File:                PWM8_Module.c
 * Author:              Provatos Eleftherios
 * Comments:            For use with PIC18F26K83 in OpenServoCAN project
 * Revision history:    V1.00
 */

/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
/* ************************************************************************** */

#include "PWM8_Module.h"
#include "Timer_2.h"
#include "Timer_4.h"
#include "Timer_6.h"

/* ************************************************************************** */
/* ************************************************************************** */
/* Section: File Scope or Global Data                                         */
/* ************************************************************************** */
/* ************************************************************************** */

static uint16_t u16_pwm_val_int = 0;

/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Local Functions                                                   */
/* ************************************************************************** */
/* ************************************************************************** */

// Sets the Timer Source for the PWM 5 Module
static int8_t PWM_8_Set_Timer_Source ( uint8_t timer ) {
    // Check the input if it is in range 0x01 - 0x03
    if ( !( CCPTMRS1_P8TSEL_MASK & timer ) ) {
        // Exit with Error
        return -1;
    }
    // Set the register without changing other bits
    CCPTMRS1 = ( CCPTMRS1 & ~CCPTMRS1_P8TSEL_MASK ) | timer;
    // Return to the point of call with success
    return 1;
}

/* ************************************************************************** */
/* ************************************************************************** */
// Section: Interface Functions                                               */
/* ************************************************************************** */
/* ************************************************************************** */

// Sets the Enable / Disable of the PWM 8 Module
void PWM_8_Set_Enable ( bool en ) {
    // Sets the enable bit according to the input
    if ( en ) {
        // Activate the module
        PWM8CONbits.EN = 1;
    }
    else {
        // Deactivate the module
        PWM8CONbits.EN = 0;
    }
    // Return to the point of call
    return;
}

// Get the Enable / Disable Status of PWM 8 Module
bool PWM_8_Get_Enable ( void ) {
    // Returns the enable bit of the configuration register
    return PWM8CONbits.EN;
}

// Sets the Polarity bit of the PWM 8 Module
void PWM_8_Set_Polarity ( bool inv ) {
    // Sets the polarity of the output
    if ( inv ) {
        // Set to inverted polarity
        PWM8CONbits.POL = 1;
    }
    else {
        // Sets to non - inverted polarity
        PWM8CONbits.POL = 0;
    }
    // Return to the point of call
    return;
}

// Inverts the polarity of the output of PWM 8 Module
void PWM_8_Invert_Polarity ( void ) {
    // Inverts the polarity based on previous state
    if ( PWM8CONbits.POL ) {
        // Since bit is set, reset
        PWM8CONbits.POL = 0;
    }
    else {
        // Since bit is reset, set
        PWM8CONbits.POL = 1;
    }
    // Return to the point of call
    return;
}

// Get the Current Polarity of the output of PWM 8 Module
bool PWM_8_Get_Polarity ( void ) {
    // Returns the polarity bit of the configuration register
    return PWM8CONbits.POL;
}

// Returns the Timer Source of PWM 8 Module
uint8_t PWM_8_Get_Timer_Source ( void ) {
    // Return the Timer settings of PWM 8 Module
    return ( CCPTMRS1 & CCPTMRS1_P8TSEL_MASK );
}

// Set the output with basic check
int8_t PWM_8_Set_Output_No_Cap ( uint16_t pwm_val ) {
    // Check if the value is in range
    if ( pwm_val > 0x3FF ) {
        // Exit with error
        return -1;
    }
    // Check to see if the Value is the old one
    if ( u16_pwm_val_int == pwm_val ) {
        // Exit with no action
        return 0;
    }
    // Update the new value
    u16_pwm_val_int = pwm_val;
    // Load the Timer registers
    PWM8DCH = ( uint8_t ) ( ( pwm_val >> 2 ) & 0xFF );
    PWM8DCL = ( uint8_t ) ( ( pwm_val & 0x03 ) << 0x06 );
    // Exit to program with success
    return 1;
}

// Set the output with Timer Period check check
int8_t PWM_8_Set_Output_Capped ( uint16_t pwm_val ) {
    // Check if the value is in range
    if ( pwm_val > 0x3FF ) {
        // Exit with error
        return -1;
    }
    // Check to see if the Value is the old one
    if ( u16_pwm_val_int == pwm_val ) {
        // Exit with no action
        return 0;
    }
    // Cap the Value according to the corresponding Timer period value
    switch ( PWM_8_Get_Timer_Source ( ) ) {
        // Case TMR2 is used, cap based on TMR2PR
        case CCPTMRS1_P8TSEL_TMR2 : {
            // Temporary variable
            uint16_t temp = ( uint16_t ) Timer_2_Period_Get ( ) << 2;
            // Check for the value
            if ( pwm_val > temp ) {
                // Cap the PWM Value
                pwm_val = temp;
            }
            // Exit switch
            break;
        }
        // Case TMR4 is used, cap based on TMR2PR
        case CCPTMRS1_P8TSEL_TMR4 : {
            // Temporary variable
            uint16_t temp = ( ( uint16_t ) Timer_4_Period_Get ( ) ) << 2;
            // Check for the value
            if ( pwm_val > temp ) {
                // Cap the PWM Value
                pwm_val = temp;
            }
            // Exit switch
            break;
        }
        // Case TMR6 is used, cap based on TMR2PR
        case CCPTMRS1_P8TSEL_TMR6 : {
            // Temporary variable
            uint16_t temp = ( ( uint16_t ) Timer_6_Period_Get ( ) ) << 2;
            // Check for the value
            if ( pwm_val > temp ) {
                // Cap the PWM Value
                pwm_val = temp;
            }
            // Exit switch
            break;
        }
        // Case something is wrong
        default : {
            // Exit with an error - Timer source error
            return -1;
        }
    }
    // Update the new value
    u16_pwm_val_int = pwm_val;
    // Load the Timer registers
    PWM8DCH = ( uint8_t ) ( ( pwm_val >> 2 ) & 0xFF );
    PWM8DCL = ( uint8_t ) ( ( pwm_val & 0x03 ) << 0x06 );
    // Exit to program with success
    return 1;
}

// Initialize the module
// Timer source, output inverted or not, start at end of initialization
int8_t PWM_8_Initialize ( uint8_t timer, bool out_inv, bool start ) {
    // Store the status of the module
    uint8_t temp_con = PWM8CON;
    // Stop the module if it is being used
    PWM8CON = 0x00;
    // Set the new timer source and check if the Source changed correctly
    if ( 0 > PWM_8_Set_Timer_Source ( timer ) ) {
        // An error was detected with input - return to previous configuration
        PWM8CON = temp_con;
        // Return with error
        return -1;
    }
    // Reset the PWM Values
    PWM8DCH = 0x00; 
    PWM8DCL = 0x00;
    // Set the polarity of the output according to new input
    PWM_8_Set_Polarity ( out_inv );
    // If start is forced the start the PWM output
    PWM_8_Set_Enable ( start );
    // Return to the point of call with success
    return 1;
}