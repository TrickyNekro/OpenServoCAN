/* 
 * File:                configuration_pins.h
 * Author:              Provatos Eleftherios
 * Comments:            For use with PIC18F26K83 in OpenServoCAN project
 * Revision history:    V1.00
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef _CONFIGURATION_PINS_H
#define	_CONFIGURATION_PINS_H

/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
/* ************************************************************************** */

#include <xc.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */
    
/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Constants                                                         */
/* ************************************************************************** */
/* ************************************************************************** */
    
#define CONFIG_LOAD_ENCODER_FWR         0x01
#define CONFIG_LOAD_ENCODER_RSV         0x02
#define CONFIG_LOAD_ANALOG_A            0x11
#define CONFIG_LOAD_ANALOG_B            0x12
    
#define PPS_PORT_X_PIN_0                0x00
#define PPS_PORT_X_PIN_1                0x01
#define PPS_PORT_X_PIN_2                0x02
#define PPS_PORT_X_PIN_3                0x03
#define PPS_PORT_X_PIN_4                0x04
#define PPS_PORT_X_PIN_5                0x05
#define PPS_PORT_X_PIN_6                0x06
#define PPS_PORT_X_PIN_7                0x07
    
#define PPS_PORT_A_PIN_X                0x00
#define PPS_PORT_B_PIN_X                0x08
#define PPS_PORT_C_PIN_X                0x10
    
/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Data Types                                                        */
/* ************************************************************************** */
/* ************************************************************************** */

/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Interface Functions                                               */
/* ************************************************************************** */
/* ************************************************************************** */
 
void    PINS_Direction_Configure_Active     ( void );
void    PINS_Direction_Configure_Sleep      ( void );
void    PINS_Peripherals_Configure_Active   ( void );
void    PINS_Peripherals_Configure_Sleep    ( void );
uint8_t PINS_Get_Config_Load                ( void );
void    PINS_Set_Config_Load                ( uint8_t config );

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* CONFIGURATION_PINS_H */

