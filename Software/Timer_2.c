/* 
 * File:                Timer_2.c
 * Author:              Provatos Eleftherios
 * Comments:            For use with PIC18F26K83 in OpenServoCAN project
 * Revision history:    V1.00
 */

/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
/* ************************************************************************** */

#include "Timer_2.h"

/* ************************************************************************** */
/* ************************************************************************** */
/* Section: File Scope or Global Data                                         */
/* ************************************************************************** */
/* ************************************************************************** */


/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Local Functions                                                   */
/* ************************************************************************** */
/* ************************************************************************** */

// Set the mode of operation in the T2HLT Register
static int8_t Timer_2_T2HLT_Set ( uint8_t pres_sync, uint8_t pres_edge,
                            uint8_t start_sync, uint8_t mode, bool up_live ) {
    // Check to see if the Timer 2 is running. To avoid erratic behavior 
    // always and only update the registers when Timer 2 is NOT running.
    if ( ( T2CONbits.ON ) && ( !up_live ) ) {
        // Return with a No Change Flag
        return 0;
    }
    // Check for illegal values
    // Illegal values of mode
    if ( ( 0x10 == mode ) || ( 0x14 == mode ) 
      || ( 0x15 == mode ) || ( 0x18 <= mode ) ) {
        // Return a fault code
        return -1;
    }
    // Illegal values of T2HLT.PSYNC
    if ( ( T2HLT_PSYNC_ON != pres_sync ) &&
         ( T2HLT_PSYNC_OFF != pres_sync ) ) {
        // Return a fault code
        return -1;
    }
    // Illegal values of T2HLT.CPOL
    if ( ( T2HLT_CKPOL_RISING != pres_edge ) && 
         ( T2HLT_CKPOL_FALLING != pres_edge ) ) {
        // Return a fault code
        return -1;
    }
    // Illegal values of T2HLT.CKSYNC
    if ( ( T2HLT_CKSYNC_ON != start_sync ) &&
         ( T2HLT_CKSYNC_OFF != start_sync ) ) {
        // Return a fault code
        return -1;
    }
    // Temporary variables
    uint8_t temp_reg = 0;
    // Combine the given values to set the T2HLT Register of Timer 2
    temp_reg = pres_sync | pres_edge | start_sync | mode;
    // Update the Timer 2 Hardware Limit Control Register
    T2HLT = temp_reg;
    // Return to the point of call with success
    return 1;
}

// Return the value of Timer 2 T2HLT Register
static uint8_t Timer_2_T2HLT_Get ( void ) {
    // Return the value
    return T2HLT;
}

// Select the clock source for Timer 2
static int8_t Timer_2_T2CLK_Set ( uint8_t clock_source, bool up_live ) {
    // Check to see if the Timer 2 is running. To avoid erratic behavior 
    // always and only update the registers when Timer 2 is NOT running.
    if ( ( T2CONbits.ON ) && ( !up_live ) ) {
        // Return with a No Change Flag
        return 0;
    }
    // Check for illegal values
    // Illegal values of T2CLK.CS
    if ( 0x0F <= clock_source ) {
        // Return a fault code
        return -1;
    }
    // Load the clock source value
    T2CLK = clock_source;
    // Return to the point of call with success
    return 1;
}

// Return the value of Timer 2 T2CLK Register
static uint8_t Timer_2_T2CLK_Get ( void ) {
    // Return the value
    return T2CLK;
}

// Select the Timer 2 Reset Signal origin
static int8_t Timer_2_T2RST_Set ( uint8_t res_source, bool up_live ) {
    // Check to see if the Timer 2 is running. To avoid erratic behavior 
    // always and only update the registers when Timer 2 is NOT running.
    if ( ( T2CONbits.ON ) && ( !up_live ) ) {
        // Return with a No Change Flag
        return 0;
    }
    // Check for illegal values
    // Illegal values of T2RST.RSEL
    if ( ( 0x01 == res_source ) || ( 0x0C == res_source ) 
      || ( 0x0D == res_source ) || ( 0x19 <= res_source ) ) {
        // Return a fault code
        return -1;
    }
    // Load the Reset Source value 
    T2RST = res_source;
    // Return to the point of call with success
    return 1;
}

// Return the value of Timer 2 T2RST Register
static uint8_t Timer_2_T2RST_Get ( void )
{
    // Return the value 
    return T2RST;
}

// Configure the Pre - Scaler and Post - Scaler setting of Timer 2
static int8_t Timer_2_T2CON_Set ( uint8_t presc, uint8_t postsc, bool up_live ){
    // Check to see if the Timer 2 is running. To avoid erratic behavior 
    // always and only update the registers when Timer 2 is NOT running.
    if ( ( T2CONbits.ON ) && ( !up_live ) ) {
        // Return with a No Change Flag
        return 0;
    }
    // Check for illegal values
    // Illegal values of T2CON.CKPS
    if ( 0x8F & presc ) {
        // Return with a fault code
        return -1;
    }
    // Illegal values of T2CON.OUTPS
    if ( 0xF0 & postsc ) {
        // Return with a fault code
        return -1;
    }
    // Temporary variables
    uint8_t temp_reg = 0;
    // Combine the given values to set the T2CON Register of Timer 2
    temp_reg = presc | postsc;
    // Update the Timer 2 Control Register
    T2CON = temp_reg;
    // Return to the point of call with success
    return 1;
}

// Return the value of Timer 2 T2CON Register
static uint8_t Timer_2_T2CON_Get ( void ) {
    // Return the value
    return T2CON;
}

// Returns the Enable status of the Interrupt
static bool Timer_2_Get_Inter_Status ( void ) {
    // Returns the enable status of Interrupts
    return PIE4bits.TMR2IE;
}

// Sets the Enable status for the Interrupt
static void Timer_2_Set_Inter_Status ( bool int_en ) {
    // Sets the enable bit of the Interrupts
    PIE4bits.TMR2IE = int_en;
    // Return to the point of call
    return;
}

// Returns the priority of the Interrupt
static bool Timer_2_Get_Inter_Priori ( void ) {
    // Returns the priority set bit of the Interrupt
    return IPR4bits.TMR2IP;
}

// Sets the Enable status for the Interrupt
static void Timer_2_Set_Inter_Priori ( bool int_pr ) {
    // Sets the enable bit of the Interrupts
    IPR4bits.TMR2IP = int_pr;
    // Return to the point of call
    return;
}

/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Interface Functions                                               */
/* ************************************************************************** */
/* ************************************************************************** */

// Return the current value of Timer 2
uint8_t Timer_2_Value_Get ( void )
{
    // Return the value
    return T2TMR;
}

// Set the value of Timer 2
void Timer_2_Value_Set ( uint8_t value )
{
    // Set the value of Timer 2
    T2TMR = value;
    // Return to the point of call
    return;
}

// Return the current value of the Timer 2 Period Register
uint8_t Timer_2_Period_Get ( void ) {
    // Return the value
    return T2PR;
}

// Set the value of Timer 2 Period
void Timer_2_Period_Set ( uint8_t value ) {
    // Set the value of Timer 2 Period
    T2PR = value;
    // Return to the point of call
    return;
}

// Enable the Interrupt
void Timer_2_Interr_ON ( void ) {
    // Enables the Interrupts for Timer 2
    PIE4bits.TMR2IE = 1;
    // Return to the point of call
    return;
}

// Disable the Interrupt
void Timer_2_Interr_OFF ( void ) {
    // Disables the Interrupts for Timer 2
    PIE4bits.TMR2IE = 0;
    // Return to the point of call
    return;
}

// Enable the Interrupt
void Timer_2_Interr_High ( void ) {
    // Set Timer 2 Interrupt Priority High
    IPR4bits.TMR2IP = 0;
    // Return to the point of call
    return;
}

// Enable the Interrupt
void Timer_2_Interr_Low ( void ) {
    // Set Timer 2 Interrupt Priority Low
    IPR4bits.TMR2IP = 1;
    // Return to the point of call
    return;
}

// Start Timer 2. Actual start of counting 
// depends on mode of operation
void Timer_2_Start ( void ) {
    // Set the ON bit of Timer 2 Control Register
    T2CONbits.ON = 1;
    // Return to the point of call
    return;
}

// Stop Timer 2. Effect immediate
void Timer_2_Stop ( void ) {
    // Reset the ON bit of Timer 2 Control Register
    T2CONbits.ON = 0;
    // Return to the point of call
    return;
}

// Return if the Timer 2 is Running or Not
bool Timer_2_Status_Get ( void ) {
    if ( T2CONbits.ON ) {
        // Return that Timer 2 is running
        return true;
    }
    else {
        // Return that Timer 2 is stopped
        return false;
    }
    // Fail safe return
    return false;
}

// Configures the Timer 2 settings.
// Timer 2 has to be stopped before changing any values. Forcing the Timer
// to be stopped can be made externally or by setting force_stop to true.
// Restarting Timer 2 after a successful configuration can done by setting
// force_start flag to true, else Timer 2 has to be started manually.
int8_t Timer_2_Configure ( uint8_t presc, uint8_t postsc, uint8_t clock_source,
                        uint8_t period, uint8_t reset_source, uint8_t mode,
                        uint8_t presc_sync, uint8_t clock_edge,
                        uint8_t start_sync, bool force_stop, 
                        bool force_start, bool int_en, bool int_pr ) {
    // Temporary variables, save status of registers before executing
    int8_t  temp_status = 0;
    uint8_t temp_T2HLT = Timer_2_T2HLT_Get ( );
    uint8_t temp_T2RST = Timer_2_T2RST_Get ( );
    uint8_t temp_T2CLK = Timer_2_T2CLK_Get ( );
    uint8_t temp_T2CON = Timer_2_T2CON_Get ( );
    bool    temp_st_IE = Timer_2_Get_Inter_Status ( );
    bool    temp_st_IP = Timer_2_Get_Inter_Priori ( );
    // If the force_stop is set to true then stop the Timer before updating
    if ( force_stop ) {
        Timer_2_Stop ( );
    }
    // Check to see if the Timer 2 is running. To avoid erratic behavior 
    // always and only update the registers when Timer 2 is NOT running.
    if ( T2CONbits.ON ) {
        // Return with a No Change Flag
        return 0;
    }
    // Try setting the T2HLT Register
    if ( -1 == Timer_2_T2HLT_Set ( presc_sync, clock_edge, start_sync, 
                                    mode, false ) ) {
        // Store the fault
        temp_status -= 1;
    }
    
    // Try setting the T2RST Register
    if ( -1 == Timer_2_T2RST_Set ( reset_source, false ) ) {
        // Store the fault
        temp_status -= 1;
    }
    // Try updating the T2CLK Register
    if ( -1 == Timer_2_T2CLK_Set ( clock_source, false ) ) {
        // Store the fault
        temp_status -= 1;
    }
    // Try updating the T2CON Register
    if ( -1 == Timer_2_T2CON_Set ( presc, postsc, false ) ) {
        // Store the fault
        temp_status -= 1;
    }
    // If a fault was detected then restore the values of the registers
    // and return to the point of call with a fault code
    if ( 0 > temp_status ) {
        // Store the recalled values
        T2HLT = temp_T2HLT;
        T2RST = temp_T2RST;
        T2CLK = temp_T2CLK;
        T2CON = temp_T2CON;
        // Store the old Interrupt settings
        Timer_2_Set_Inter_Status ( temp_st_IE );
        Timer_2_Set_Inter_Priori ( temp_st_IP );
        // Return with a fault code
        return temp_status;
    }
    // Set the input interrupt settings
    Timer_2_Set_Inter_Status ( int_en );
    Timer_2_Set_Inter_Priori ( int_pr );
    // Set the Timer Period
    Timer_2_Period_Set ( period );
    // Start Timer 2 again if requested
    if( force_start ) {
        // Start Timer 2
        Timer_2_Start ( );
    }
    // Return to the point of call
    return 1;
}

/* ************************************************************************** */
/* ************************************************************************** */
// Section: Interrupt Functions                                               */
/* ************************************************************************** */
/* ************************************************************************** */

// Any Priority Interrupt Vector for Vectored Interrupts MVECEN = ON
void __interrupt ( irq ( IRQ_TMR2 ) ) TMR2_Isr ( void ) {
    // Interrupt service routine for CCP1 Module
    // First Reset the Flag
    PIR4bits.TMR2IF = 0;
    
}

