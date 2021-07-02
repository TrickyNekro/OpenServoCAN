/* 
 * File:                configuration_pins.c
 * Author:              Provatos Eleftherios
 * Comments:            For use with PIC18F26K83 in OpenServoCAN project
 * Revision history:    V1.00
 */

/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
/* ************************************************************************** */

#include "configuration_pins.h"

/* ************************************************************************** */
/* ************************************************************************** */
/* Section: File Scope or Global Data                                         */
/* ************************************************************************** */
/* ************************************************************************** */

static uint8_t u8_config_load = 0;

/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Local Functions                                                   */
/* ************************************************************************** */
/* ************************************************************************** */

static void PPS_LOCK ( void )
{
    // Send first safety unlock pattern
    // Byte A
    PPSLOCK = 0x55;
    // Byte B
    PPSLOCK = 0xAA;
    // Lock the Peripheral Pin Select Module
    PPSLOCKbits.PPSLOCKED = 0x01;
    // Return to the point of call
    return;
}

static void PPS_UNLOCK ( void )
{
    // Send first safety unlock pattern
    // Byte A
    PPSLOCK = 0x55;
    // Byte B
    PPSLOCK = 0xAA;
    // Lock the Peripheral Pin Select Module
    PPSLOCKbits.PPSLOCKED = 0x00;
    // Return to the point of call
    return;
}

/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Interface Functions                                               */
/* ************************************************************************** */
/* ************************************************************************** */


// Configure the pins based on the stored load-out for operation
// in case that the EEPROM position is corrupt, load defaults
void PINS_Direction_Configure_Active ( void )
{
    // Load default configuration
    // PORTA - Inputs either Encoder or Potentiometer
    TRISA    =  0x1B;
    // A digital device is assumed being connected
    // All inputs digital
    ANSELA  =   0x00;
    // Activate weak pull-ups on input to stop 
    // port from collecting noise 
    WPUA    =   0x1B;
    
    // PORTB - Indicators - CAN TX / STBY - USART - PROG_PORT
    TRISB    =  0xF0;
    // All pins are digital
    ANSELB  =   0x00;
    // Weak Pull - Up for the USART RXD
    WPUB    =   0xF0;
    
    // PORTC - CAN RX / NSIL - PWR_EN - ADC V / I - PWM A / B
    TRISC    =  0x3C;
    // ADC Inputs are Analog
    ANSELC  =   0x00;
    // All pins are driving or driven, no need for pull ups
    WPUC    =   0x38;
    
    // Return to program
    return;
}

// Configure the pins based on the stored load out for device sleep
// in case that the EEPROM position is corrupt, load defaults
void PINS_Direction_Configure_Sleep ( void )
{
    // Return to program
    return;
}

// Configure the peripheral connection to pins (PPS) based on the
// stored load-out for operation in case that the EEPROM 
// position is corrupt, load defaults
void PINS_Peripherals_Configure_Active ( void )
{
    // First execute the sequence to unlock the PPS Module
    PPS_UNLOCK();
    // Connect PWM 8 to RA.7, LED - GREEN
    RA6PPS = PPS_PWM_8_TO_PIN;
    // Connect PWM 7 to RA.6, LED - BLUE
    RA7PPS = PPS_PWM_6_TO_PIN;
    // Connect PWM 6 to RA.5, LED - RED
    RA5PPS = PPS_PWM_5_TO_PIN;
    // Lastly execute the sequence to lock the PPS Module
    PPS_LOCK();
    // Return to program
    return;
}

// Configure the peripheral connection to pins based on the 
// stored load out for device sleep in case that the EEPROM
// position is corrupt, load defaults
void PINS_Peripherals_Configure_Sleep ( void )
{
    // Return to program
    return;
}

// Return the type of load-out currently used
uint8_t PINS_Get_Config_Load ( void )
{
    // Return to program with value
    return u8_config_load;
}

// Sets the type of load-out currently used
void PINS_Set_Config_Load ( uint8_t config )
{
    // Set Value
    u8_config_load = config;
    // Return to program
    return;
}