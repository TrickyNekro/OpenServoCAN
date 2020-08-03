/* 
 * File:                CCP4_Module.h
 * Author:              Provatos Eleftherios
 * Comments:            For use with PIC18F26K83 in OpenServoCAN project
 * Revision history:    V1.00
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef _CCP4_MODULE_H
#define	_CCP4_MODULE_H

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
    
// Mode Selection for CCP1 Module Clocking
#define CCP4_CCP4CON_MODE_DISABLE                           0x00
#define CCP4_CCP4CON_MODE_COMP_TOGGLE_CLEAR_TMR1            0x01
#define CCP4_CCP4CON_MODE_COMP_TOGGLE_ONLY                  0x02
#define CCP4_CCP4CON_MODE_CAPT_EVERY_CHANGE                 0x03
#define CCP4_CCP4CON_MODE_CAPT_EVERY_FALLING                0x04
#define CCP4_CCP4CON_MODE_CAPT_EVERY_RISING                 0x05
#define CCP4_CCP4CON_MODE_CAPT_EVERY_4TH_RISING             0x06
#define CCP4_CCP4CON_MODE_CAPT_EVERY_16TH_RISING            0x07
#define CCP4_CCP4CON_MODE_COMP_SET_OUTPUT                   0x08
#define CCP4_CCP4CON_MODE_COMP_RESET_OUTPUT                 0x09
#define CCP4_CCP4CON_MODE_COMP_PULSE_OUTPUT                 0x0A
#define CCP4_CCP4CON_MODE_COMP_PULSE_OUTPUT_CLEAR_TMR1      0x0B
#define CCP4_CCP4CON_MODE_PWM                               0x0C
    
// Select Related Timer Module to the CCP Module
// #define CCP1_CCPTMRS0_C1SEL_TIMER_2_1                    0x01
// #define CCP1_CCPTMRS0_C1SEL_TIMER_4_3                    0x02
// #define CCP1_CCPTMRS0_C1SEL_TIMER_6_5                    0x03
// Select Related Timer Module to the CCP Module
// #define CCP2_CCPTMRS0_C2SEL_TIMER_2_1                    0x04
// #define CCP2_CCPTMRS0_C2SEL_TIMER_4_3                    0x08
// #define CCP2_CCPTMRS0_C2SEL_TIMER_6_5                    0x0C
// Select Related Timer Module to the CCP Module
// #define CCP3_CCPTMRS0_C3SEL_TIMER_2_1                    0x10
// #define CCP3_CCPTMRS0_C3SEL_TIMER_4_3                    0x20
// #define CCP3_CCPTMRS0_C3SEL_TIMER_6_5                    0x30
// Select Related Timer Module to the CCP Module
#define CCP4_CCPTMRS0_C4SEL_TIMER_2_1                       0x40
#define CCP4_CCPTMRS0_C4SEL_TIMER_4_3                       0x80
#define CCP4_CCPTMRS0_C4SEL_TIMER_6_5                       0xC0
// Select Related Timer Module to the CCP Module
// #define PWM5_CCPTMRS1_P5TSEL_TIMER_2                     0x01
// #define PWM5_CCPTMRS1_P5TSEL_TIMER_4                     0x02
// #define PWM5_CCPTMRS1_P5TSEL_TIMER_6                     0x03
// Select Related Timer Module to the CCP Module
// #define PWM6_CCPTMRS1_P6TSEL_TIMER_2                     0x04
// #define PWM6_CCPTMRS1_P6TSEL_TIMER_4                     0x08
// #define PWM6_CCPTMRS1_P6TSEL_TIMER_6                     0x0C
// Select Related Timer Module to the CCP Module
// #define PWM7_CCPTMRS1_P7TSEL_TIMER_2                     0x10
// #define PWM7_CCPTMRS1_P7TSEL_TIMER_4                     0x20
// #define PWM7_CCPTMRS1_P7TSEL_TIMER_6                     0x30
// Select Related Timer Module to the CCP Module
// #define PWM8_CCPTMRS1_P8TSEL_TIMER_2                     0x40
// #define PWM8_CCPTMRS1_P8TSEL_TIMER_4                     0x80
// #define PWM8_CCPTMRS1_P8TSEL_TIMER_6                     0xC0
    
// Select for the Capture Input Input Selection
#define CCP4_CCP4CAP_CTS_CCP4PPS                            0x00
#define CCP4_CCP4CAP_CTS_CMP1_OUTPUT                        0x01
#define CCP4_CCP4CAP_CTS_CMP2_OUTPUT                        0x02
#define CCP4_CCP4CAP_CTS_IOC_INT                            0x03
#define CCP4_CCP4CAP_CTS_CLC1_OUT                           0x04
#define CCP4_CCP4CAP_CTS_CLC2_OUT                           0x05
#define CCP4_CCP4CAP_CTS_CLC3_OUT                           0x06
#define CCP4_CCP4CAP_CTS_CLC4_OUT                           0x07
#define CCP4_CCP4CAP_CTS_CAN_RX                             0x08
    
// CCP1CON MASKS
#define CCP4_CCP4CON_EN_MASK                                0x80
#define CCP4_CCP4CON_OUT_MASK                               0x20
#define CCP4_CCP4CON_FMT_MASK                               0x10
#define CCP4_CCP4CON_MODE_MASK                              0x0F
    
// CCP1CAP MASKS
#define CCP4_CCP4CAP_CTS_MASK                               0x0F
    
// CCPTMRS0 MASKS
// #define CCP1_CCPTMRS0_C1TSEL_MASK                        0x03
// #define CCP2_CCPTMRS0_C2TSEL_MASK                        0x0C
// #define CCP3_CCPTMRS0_C3TSEL_MASK                        0x30
#define CCP4_CCPTMRS0_C4TSEL_MASK                           0xC0
    
// CCPTMRS1 MASKS
// #define PWM5_CCPTMRS1_P5TSEL_MASK                        0x03
// #define PWM6_CCPTMRS1_P6TSEL_MASK                        0x0C
// #define PWM7_CCPTMRS1_P7TSEL_MASK                        0x30
// #define PWM8_CCPTMRS1_P8TSEL_MASK                        0xC0
    
// Interrupt Enable Masks
// #define CCP1_PIE4_CCP1IE_MASK                            0x08
// #define CCP2_PIE8_CCP2IE_MASK                            0x08
// #define CCP3_PIE9_CCP3IE_MASK                            0x04
#define CCP4_PIE9_CCP4IE_MASK                               0x20
    
// Interrupt Flag Masks
// #define CCP1_PIR4_CCP1IF_MASK                            0x08
// #define CCP2_PIR8_CCP2IF_MASK                            0x08
// #define CCP3_PIR9_CCP3IF_MASK                            0x04
#define CCP4_PIR9_CCP4IF_MASK                               0x20
    
// Interrupt Priority Mask
// #define CCP1_IPR4_CCP1IP_MASK                            0x08
// #define CCP2_IPR8_CCP2IP_MASK                            0x08
// #define CCP3_IPR9_CCP3IP_MASK                            0x04
#define CCP4_IPR9_CCP4IP_MASK                               0x20
    
// Basic Control Operations for CCP2 Module
#define CCP4_CCP4CON_ENABLE_MODULE()                        (CCP4CON |= CCP4_CCP4CON_EN_MASK)
#define CCP4_CCP4CON_DISABLE_MODULE()                       (CCP4CON &= ~CCP4_CCP4CON_EN_MASK)
#define CCP4_CCP4CON_RIGHT_ADJUST_DATA()                    (CCP4CON &= ~CCP4_CCP4CON_FMT_MASK)
#define CCP4_CCP4CON_LEFT_ADJUST_DATA()                     (CCP4CON |= CCP4_CCP4CON_FMT_MASK)
#define CCP4_ENABLE_INTERRUPT()                             (PIE9    |= CCP4_PIE9_CCP4IE_MASK)
#define CCP4_DISABLE_INTERRUPT()                            (PIE9    &= ~CCP4_PIE9_CCP4IE_MASK)
#define CCP4_CLEAR_INTERRUPT_FLAG()                         (PIR9    &= ~CCP4_PIR9_CCP4IF_MASK)
#define CCP4_INTERRUPT_SET_HIGH_PRIORITY()                  (IPR9    |= CCP4_IPR9_CCP4IP_MASK)
#define CCP4_INTERRUPT_SET_LOW_PRIORITY()                   (IPR9    &= ~CCP4_IPR9_CCP4IP_MASK)
    
/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Interface Functions                                               */
/* ************************************************************************** */
/* ************************************************************************** */
    
uint8_t     CCP4_Module_Enable          ( bool en );
bool        CCP4_Module_Get_EN_State    ( void );
bool        CCP4_Module_Get_OUT_State   ( void );
bool        CCP4_Module_Get_Data_Align  ( void );
uint8_t     CCP4_Module_Get_Mode        ( void );
uint16_t    CCP4_Module_Get_Value       ( void );
int8_t      CCP4_Module_Set_Value       ( uint16_t value );
int8_t      CCP4_Module_Config          ( uint8_t mode, uint8_t timer_sel,
                                          uint8_t capt_in, bool left_adj,
                                          bool int_en, bool int_hi_pri, bool en );
    
#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* XC_HEADER_TEMPLATE_H */
