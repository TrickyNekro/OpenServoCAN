/* 
 * File:                CWG1_Module.h
 * Author:              Provatos Eleftherios
 * Comments:            For use with PIC18F26K83 in OpenServoCAN project
 * Revision history:    V1.00
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef _CWG1_MODULE_H
#define	_CWG1_MODULE_H

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
    
// Mode Selection for the CWG1 Module
#define CWG1_CWG1CON0_MODE_ASYNC_STEER                      0x00
#define CWG1_CWG1CON0_MODE_SYNC_STEER                       0x01
#define CWG1_CWG1CON0_MODE_FR_FULL_BRIDGE                   0x02
#define CWG1_CWG1CON0_MODE_BW_FULL_BRIDGE                   0x03
#define CWG1_CWG1CON0_MODE_HALF_BRIDGE                      0x04
#define CWG1_CWG1CON0_MODE_PUSH_PULL                        0x05
#define CWG1_CWG1CON0_MODE_RESERVED_1                       0x06
#define CWG1_CWG1CON0_MODE_RESERVED_2                       0x07
    
// CWG1CON0 Masks
#define CWG1_CWG1CON0_MODE_MASK                             0x07
#define CWG1_CWG1CON0_LD_MASK                               0x40
#define CWG1_CWG1CON0_EN_MASK                               0x80
    
// Output Polarity for the CWG1 Module
#define CWG1_CWG1CON1_POL_INV_A                             0x01
#define CWG1_CWG1CON1_POL_INT_B                             0x02
#define CWG1_CWG1CON1_POL_INT_C                             0x04
#define CWG1_CWG1CON1_POL_INT_D                             0x08
    
// CWG1CON1 Masks
#define CWG1_CWG1CON1_POL_X_MASK                            0x0F
#define CWG1_CWG1CON1_POL_A_BIT                             CWG1CON1bits.POLA
#define CWG1_CWG1CON1_POL_B_BIT                             CWG1CON1bits.POLB
#define CWG1_CWG1CON1_POL_C_BIT                             CWG1CON1bits.POLC
#define CWG1_CWG1CON1_POL_D_BIT                             CWG1CON1bits.POLD
#define CWG1_CWG1CON1_GET_INPUT_MASK                        0x20
#define CWG1_CWG1CON1_GET_INPUT                             CWG1CON1bits.IN
    
// Select Clock Input for the CWG1 Module
#define CWG1_CWG1CLK_HFINTOSC                               0x01
#define CWG1_CWG1CLK_FOSC                                   0x00
#define CWG1_CWG1CLK_BIT                                    CWG1CLK.CS
    
// Input selection for the CWG1 Module
#define CWG1_CWG1ISM_IS_CWG1PPS                             0x00
#define CWG1_CWG1ISM_IS_CCP1_OUT                            0x01
#define CWG1_CWG1ISM_IS_CCP2_OUT                            0x02
#define CWG1_CWG1ISM_IS_CCP3_OUT                            0x03
#define CWG1_CWG1ISM_IS_CCP4_OUT                            0x04
#define CWG1_CWG1ISM_IS_PWM5_OUT                            0x05
#define CWG1_CWG1ISM_IS_PWM6_OUT                            0x06
#define CWG1_CWG1ISM_IS_PWM7_OUT                            0x07
#define CWG1_CWG1ISM_IS_PWM8_OUT                            0x08
#define CWG1_CWG1ISM_IS_RESERVED_1                          0x09
#define CWG1_CWG1ISM_IS_RESERVED_2                          0x0A
#define CWG1_CWG1ISM_IS_NCO1OUT                             0x0B
#define CWG1_CWG1ISM_IS_CMP1OUT                             0x0C
#define CWG1_CWG1ISM_IS_CMP2OUT                             0x0D
#define CWG1_CWG1ISM_IS_DSM_OUT                             0x0E
#define CWG1_CWG1ISM_IS_CLC1_OUT                            0x0F
#define CWG1_CWG1ISM_IS_CLC2_OUT                            0x10
#define CWG1_CWG1ISM_IS_CLC3_OUT                            0x11
#define CWG1_CWG1ISM_IS_CLC4_OUT                            0x12
#define CWG1_CWG1ISM_IS_RESERVED_3                          0x13
    
// CWG1ISM Masks
#define CWG1_CWG1ISM_IS_MASK                                0x1F
    
// Steering and Override Options for CWG1 Module
#define CWG1_CWG1STR_OVR_A_EN                               0x00
#define CWG1_CWG1STR_OVR_A_DIS                              0x01
#define CWG1_CWG1STR_OVR_B_EN                               0x00
#define CWG1_CWG1STR_OVR_B_DIS                              0x02
#define CWG1_CWG1STR_OVR_C_EN                               0x00
#define CWG1_CWG1STR_OVR_C_DIS                              0x04
#define CWG1_CWG1STR_OVR_D_EN                               0x00
#define CWG1_CWG1STR_OVR_D_DIS                              0x08
    
// Steering and Overide Output States for CWG1 Module
#define CWG1_CWG1STR_OVR_A_STATE_HIGH                       0x10
#define CWG1_CWG1STR_OVR_A_STATE_LOW                        0x00
#define CWG1_CWG1STR_OVR_B_STATE_HIGH                       0x20
#define CWG1_CWG1STR_OVR_B_STATE_LOW                        0x00
#define CWG1_CWG1STR_OVR_C_STATE_HIGH                       0x40
#define CWG1_CWG1STR_OVR_C_STATE_LOW                        0x00
#define CWG1_CWG1STR_OVR_D_STATE_HIGH                       0x80
#define CWG1_CWG1STR_OVR_D_STATE_LOW                        0x00

// CWG1STR Masks
#define CWG1_CWG1STR_OVR_EN_MASK                            0x0F
#define CWG1_CWG1STR_OVR_STATE_MASK                         0xF0
#define CWG1_CWG1STR_OVR_A_EN_BIT                           CWG1STRbits.STRA
#define CWG1_CWG1STR_OVR_B_EN_BIT                           CWG1STRbits.STRB
#define CWG1_CWG1STR_OVR_C_EN_BIT                           CWG1STRbits.STRC
#define CWG1_CWG1STR_OVR_D_EN_BIT                           CWG1STRbits.STRD
#define CWG1_CWG1STR_OVR_A_STATE_BIT                        CWG1STRbits.OVRA
#define CWG1_CWG1STR_OVR_B_STATE_BIT                        CWG1STRbits.OVRB
#define CWG1_CWG1STR_OVR_C_STATE_BIT                        CWG1STRbits.OVRC
#define CWG1_CWG1STR_OVR_D_STATE_BIT                        CWG1STRbits.OVRD
    
// Auto-Shutdown Options of the CWG1 Module
#define CWG1_CWG1AS0_LSAC_OUTS_INACTIVE                     0x00
#define CWG1_CWG1AS0_LSAC_OUTS_TRISTATE                     0x04
#define CWG1_CWG1AS0_LSAC_OUTS_LOW                          0x08
#define CWG1_CWG1AS0_LSAC_OUTS_HIGH                         0x0C
#define CWG1_CWG1AS0_LSBD_OUTS_INACTIVE                     0x00
#define CWG1_CWG1AS0_LSBD_OUTS_TRISTATE                     0x10
#define CWG1_CWG1AS0_LSBD_OUTS_LOW                          0x20
#define CWG1_CWG1AS0_LSBD_OUTS_HIGH                         0x30
#define CWG1_CWG1AS0_RESTART_EN                             0x40
#define CWG1_CWG1AS0_RESTART_DIS                            0x00
#define CWG1_CWG1AS0_AUTO_STDN_EN                           0x80
#define CWG1_CWG1AS0_AUTO_STDN_DIS                          0x00
    
// CWG1AS0 Masks
#define CWG1_CWG1AS0_LSAC_OUTS_MASK                         0x0C
#define CWG1_CWG1AS0_LSBD_OUTS_MASK                         0x30
#define CWG1_CWG1AS0_RESTART_EN_BIT                         CWG1AS0bits.REN
#define CWG1_CWG1AS0_AUTO_STDN_EN_BIT                       CWG1AS0bits.SHUTDOWN
    
// Auto-Shutdown Source Select for the CWG1 Module
#define CWG1_CWG1AS1_STDN_FROM_CWG1PPS_EN                   0x01
#define CWG1_CWG1AS1_STDN_FROM_CWG1PPS_DIS                  0x00
#define CWG1_CWG1AS1_STDN_FROM_TIMER_2_POST_EN              0x02
#define CWG1_CWG1AS1_STDN_FROM_TIMER_2_POST_DIS             0x00
#define CWG1_CWG1AS1_STDN_FROM_TIMER_4_POST_EN              0x04
#define CWG1_CWG1AS1_STDN_FROM_TIMER_4_POST_DIS             0x00
#define CWG1_CWG1AS1_STDN_FROM_TIMER_6_POST_EN              0x08
#define CWG1_CWG1AS1_STDN_FROM_TIMER_6_POST_DIS             0x00
#define CWG1_CWG1AS1_STDN_FROM_CMP1_OUT_EN                  0x10
#define CWG1_CWG1AS1_STDN_FROM_CMP1_OUT_DIS                 0x00
#define CWG1_CWG1AS1_STDN_FROM_CMP2_OUT_EN                  0x20
#define CWG1_CWG1AS1_STDN_FROM_CMP2_OUT_DIS                 0x00
#define CWG1_CWG1AS1_STDN_FROM_CLC2_OUT_EN                  0x40
#define CWG1_CWG1AS1_STDN_FROM_CLC2_OUT_DIS                 0x00
    
// CWG1AS0 Masks
#define CWG1_CWG1AS1_STDN_SOURCES_MASK                      0x7F
#define CWG1_CWG1AS1_STDN_FROM_CWG1PPS                      CWG1AS1bits.AS0E
#define CWG1_CWG1AS1_STDN_FROM_TIMER_2                      CWG1AS1bits.AS1E
#define CWG1_CWG1AS1_STDN_FROM_TIMER_4                      CWG1AS1bits.AS2E
#define CWG1_CWG1AS1_STDN_FROM_TIMER_6                      CWG1AS1bits.AS3E
#define CWG1_CWG1AS1_STDN_FROM_CMP1_OUT                     CWG1AS1bits.AS4E
#define CWG1_CWG1AS1_STDN_FROM_CMP2_OUT                     CWG1AS1bits.AS5E
#define CWG1_CWG1AS1_STDN_FROM_CLC2_OUT                     CWG1AS1bits.AS6E
    
// CWG Rising Dead-Band Count Register
#define CWG1_CWG1DBR_RISING_DEAD_BAND_MAX                   0x3F
#define CWG1_CWG1DBR_RISING_DEAD_BAND_MIN                   0x00
#define CWG1_CWG1DBR_RISING_DEAD_BAND_VAL                   CWG1DBRbits.DBR
#define CWG1_CWG1DBR_FALLING_DEAD_BAND_MAX                  0x3F
#define CWG1_CWG1DBR_FALLING_DEAD_BAND_MIN                  0x00
#define CWG1_CWG1DBR_FALLING_DEAD_BAND_VAL                  CWG1DBFbits.DBF
    
    
#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* XC_HEADER_TEMPLATE_H */

