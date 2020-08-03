/* 
 * File:                Timer_6.h
 * Author:              Provatos Eleftherios
 * Comments:            For use with PIC18F26K83 in OpenServoCAN project
 * Revision history:    V1.00
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef _TIMER_6_H
#define	_TIMER_6_H

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
    
// Clock Selection Register Valid Values T6CLK
#define T6CKL_CS_T6INPPS                            0x00
#define T6CKL_CS_F_OSC_DIV_4                        0x01
#define T6CKL_CS_F_OSC_DIRECT                       0x02
#define T6CKL_CS_HF_INT_OSC                         0x03
#define T6CKL_CS_LF_INT_OSC                         0x04
#define T6CKL_CS_MF_INT_OSC_500                     0x05
#define T6CKL_CS_MF_INT_OSC_32                      0x06
#define T6CKL_CS_SOSC                               0x07
#define T6CKL_CS_CLKREF_OUT                         0x08
#define T6CKL_CS_NCO1OUT                            0x09
#define T6CKL_CS_ZCD_OUT                            0x0A
#define T6CKL_CS_CLC1_OUT                           0x0B
#define T6CKL_CS_CLC2_OUT                           0x0C
#define T6CKL_CS_CLC3_OUT                           0x0D
#define T6CKL_CS_CLC4_OUT                           0x0E
    
// Timer 6 External Reset Signal Selection Register T6RST
#define T6RST_RSEL_T6INPPS                          0x00
#define T6RST_RSEL_TMR2_POSTSCALED                  0x01
#define T6RST_RSEL_TMR4_POSTSCALED                  0x02
#define T6RST_RSEL_CCP1OUT                          0x04
#define T6RST_RSEL_CCP2OUT                          0x05
#define T6RST_RSEL_CCP3OUT                          0x06
#define T6RST_RSEL_CCP4OUT                          0x07
#define T6RST_RSEL_PWM5OUT                          0x08
#define T6RST_RSEL_PWM6OUT                          0x09
#define T6RST_RSEL_PWM7OUT                          0x0A
#define T6RST_RSEL_PWM8OUT                          0x0B
#define T6RST_RSEL_CMP1OUT                          0x0E
#define T6RST_RSEL_CMP2OUT                          0x0F
#define T6RST_RSEL_ZCD_UOT                          0x10
#define T6RST_RSEL_CLC1_OUT                         0x11
#define T6RST_RSEL_CLC2_OUT                         0x12
#define T6RST_RSEL_CLC3_OUT                         0x13
#define T6RST_RSEL_CLC4_OUT                         0x14
#define T6RST_RSEL_UART1_RX_EDGE                    0x15
#define T6RST_RSEL_UART1_TX_EDGE                    0x16
#define T6RST_RSEL_UART2_RX_EDGE                    0x17
#define T6RST_RSEL_UART2_TX_EDGE                    0x18
    
// Timer 6 Control Register T6CON
#define T6CON_ON                                    0x80
// Timer 6 Pre - Scaler Settings
#define T6CON_CKPS_PRESC_1_1                        0x00
#define T6CON_CKPS_PRESC_1_2                        0x10
#define T6CON_CKPS_PRESC_1_4                        0x20
#define T6CON_CKPS_PRESC_1_8                        0x30
#define T6CON_CKPS_PRESC_1_16                       0x40
#define T6CON_CKPS_PRESC_1_32                       0x50
#define T6CON_CKPS_PRESC_1_64                       0x60
#define T6CON_CKPS_PRESC_1_128                      0x70
// Timer 6 Post - Scaler Settings
#define T6CON_OUTPS_POST_1_1                        0x00
#define T6CON_OUTPS_POST_1_2                        0x01
#define T6CON_OUTPS_POST_1_3                        0x02
#define T6CON_OUTPS_POST_1_4                        0x03
#define T6CON_OUTPS_POST_1_5                        0x04
#define T6CON_OUTPS_POST_1_6                        0x05
#define T6CON_OUTPS_POST_1_7                        0x06
#define T6CON_OUTPS_POST_1_8                        0x07
#define T6CON_OUTPS_POST_1_9                        0x08
#define T6CON_OUTPS_POST_1_10                       0x09
#define T6CON_OUTPS_POST_1_11                       0x0A
#define T6CON_OUTPS_POST_1_12                       0x0B
#define T6CON_OUTPS_POST_1_13                       0x0C
#define T6CON_OUTPS_POST_1_14                       0x0D
#define T6CON_OUTPS_POST_1_15                       0x0E
#define T6CON_OUTPS_POST_1_16                       0x0F
    
// Timer 6 Hardware Limit Control Register T4HLT
#define T6HLT_PSYNC_ON                              0x80
#define T6HLT_PSYNC_OFF                             0x00
#define T6HLT_CKPOL_FALLING                         0x40
#define T6HLT_CKPOL_RISING                          0x00
#define T6HLT_CKSYNC_ON                             0x20
#define T6HLT_CKSYNC_OFF                            0x00
// Timer 6 Running in Free - Running Mode
#define T6HLT_MODE_FR_SOFT_GATE                     0x00
#define T6HLT_MODE_FR_HARD_GATE_HIGH                0x01
#define T6HLT_MODE_FR_HARD_GATE_LOW                 0x02
#define T6HLT_MODE_FR_RS_ACT_ON_CHANGE              0x03
#define T6HLT_MODE_FR_RS_ACT_ON_RISING              0x04
#define T6HLT_MODE_FR_RS_ACT_ON_FALLING             0x05
#define T6HLT_MODE_FR_RS_ACT_LOW                    0x06
#define T6HLT_MODE_FR_RS_ACT_HIGH                   0x07
// Timer 6 Running in One - Shot Mode
#define T6HLT_MODE_OS_START_SOFT                    0x08
#define T6HLT_MODE_OS_START_RISING                  0x09
#define T6HLT_MODE_OS_START_FALLING                 0x0A
#define T6HLT_MODE_OS_START_CHANGE                  0x0B
#define T6HLT_MODE_OS_START_RISING_RS_RISING        0x0C
#define T6HLT_MODE_OS_START_FALLING_RS_FALLING      0x0D
#define T6HLT_MODE_OS_START_RISING_RS_LOW           0x0E
#define T6HLT_MODE_OS_START_FALLING_RS_HIGH         0x0F
#define T6HLT_MODE_OS_START_HIGH_RS_LOW             0x16
#define T6HLT_MODE_OS_START_LOW_RS_HIGH             0x17
// Timer 6 Running in Mono - Stable Mode
#define T6HLT_MODE_MS_START_RISING                  0x11
#define T6HLT_MODE_MS_START_FALLING                 0x12
#define T6HLT_MODE_MS_START_CHANGE                  0x13
    
    
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
 
uint8_t     Timer_6_Value_Get   ( void );
void        Timer_6_Value_Set   ( uint8_t value );
uint8_t     Timer_6_Period_Get  ( void );
void        Timer_6_Period_Set  ( uint8_t value );
void        Timer_6_Start       ( void );
void        Timer_6_Stop        ( void );
bool        Timer_6_Status_Get  ( void );
int8_t      Timer_6_Configure   ( uint8_t presc, uint8_t postsc,
                                  uint8_t clock_source, uint8_t reset_source,
                                  uint8_t mode, uint8_t presc_sync,
                                  uint8_t clock_edge, uint8_t start_sync, 
                                  bool force_stop, bool force_start);


#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* CONFIGURATION_PINS_H */

