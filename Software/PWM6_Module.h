/* 
 * File:                PWM6_Module.h
 * Author:              Provatos Eleftherios
 * Comments:            For use with PIC18F26K83 in OpenServoCAN project
 * Revision history:    V1.00
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef _PWM_MOD_6_H
#define	_PWM_MOD_6_H

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
    
// PWM 5 Module Enable bit
#define PWM6CON_EN_ON                               0x80
#define PWM6CON_EN_OFF                              0x00
    
// PWM 5 Module Enable bit Mask
#define PWM6CON_EN_MASK                             0x80
    
// PWM 5 Polarity bit
#define PWM6CON_POL_INV                             0x10
#define PWM6CON_POL_NORM                            0x00
    
// PWM 5 Polarity bit Mask
#define PWM6CON_POL_MASK                            0x10
    
// PWM 5 Output Read bit Mask
#define PWM6COM_MASK_OUT                            0x20
    
// PWM 5 Timer Select bits
#define CCPTMRS1_P6TSEL_TMR2                        0x04
#define CCPTMRS1_P6TSEL_TMR4                        0x08
#define CCPTMRS1_P6TSEL_TMR6                        0x0C
    
// PWM 5 Timer Select bits Mask
#define CCPTMRS1_P6TSEL_MASK                        0x0C
    
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
 
void    PWM_6_Set_Enable        ( bool en );
bool    PWM_6_Get_Enable        ( void );
void    PWM_6_Set_Polarity      ( bool inv );
void    PWM_6_Invert_Polarity   ( void ); 
bool    PWM_6_Get_Polarity      ( void );
uint8_t PWM_6_Get_Timer_Source  ( void );
int8_t  PWM_6_Set_Output_No_Cap ( uint16_t pwm_val );
int8_t  PWM_6_Set_Output_Capped ( uint16_t pwm_val );
int8_t  PWM_6_Initialize        ( uint8_t timer, bool out_inv, bool start );

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* CONFIGURATION_PINS_H */

