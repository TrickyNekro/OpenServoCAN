/* 
 * File:                Timer_4.c
 * Author:              Provatos Eleftherios
 * Comments:            For use with PIC18F26K83 in OpenServoCAN project
 * Revision history:    V1.00
 */

/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
/* ************************************************************************** */

#include <pic18f26k83.h>

#include "Timer_4.h"

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

// Set the mode of operation in the T4HLT Register
static int8_t Timer_4_T4HLT_Set (uint8_t pres_sync, uint8_t pres_edge,
                            uint8_t start_sync, uint8_t mode, bool up_live ) {
    // Check to see if the Timer 4 is running. To avoid erratic behavior 
    // always and only update the registers when Timer 4 is NOT running.
    if ( ( T4CONbits.ON ) && ( !up_live ) ) {
        // Return with a No Change Flag
        return 0;
    }
    // Check for illegal values
    // Illegal values of mode
    if ( ( 0x10 == mode ) || ( 0x14 == mode ) || 
         ( 0x15 == mode ) || ( 0x18 <= mode ) ) {
        // Return a fault code
        return -1;
    }
    // Illegal values of T4HLT.PSYNC
    if ( ( T4HLT_PSYNC_ON != pres_sync ) && 
         ( T4HLT_PSYNC_OFF != pres_sync ) ) {
        // Return a fault code
        return -1;
    }
    // Illegal values of T4HLT.CPOL
    if ( ( T4HLT_CKPOL_RISING != pres_edge ) &&
         ( T4HLT_CKPOL_FALLING != pres_edge ) ) {
        // Return a fault code
        return -1;
    }
    // Illegal values of T4HLT.CKSYNC
    if ( ( T4HLT_CKSYNC_ON != start_sync ) && 
         ( T4HLT_CKSYNC_OFF != start_sync ) ) {
        // Return a fault code
        return -1;
    }
    // Temporary variables
    uint8_t temp_reg = 0;
    // Combine the given values to set the T4HLT Register of Timer 4
    temp_reg = pres_sync | pres_edge | start_sync | mode;
    // Update the Timer 4 Hardware Limit Control Register
    T4HLT = temp_reg;
    // Return to the point of call with success
    return 1;
}

// Return the value of Timer 4 T4HLT Register
static uint8_t Timer_4_T4HLT_Get ( void ) {
    // Return the value
    return T4HLT;
}

// Select the clock source for Timer 4
static int8_t Timer_4_T4CLK_Set ( uint8_t clock_source, bool up_live ) {
    // Check to see if the Timer 4 is running. To avoid erratic behavior 
    // always and only update the registers when Timer 4 is NOT running.
    if((T4CONbits.ON) && (!up_live))
    {
        // Return with a No Change Flag
        return 0;
    }
    // Check for illegal values
    // Illegal values of T4CLK.CS
    if(0x0F <= clock_source)
    {
        // Return a fault code
        return -1;
    }
    // Load the clock source value
    T4CLK = clock_source;
    // Return to the point of call with success
    return 1;
}

// Return the value of Timer 4 T4CLK Register
static uint8_t Timer_4_T4CLK_Get ( void ) {
    // Return the value
    return T4CLK;
}

// Select the Timer 4 Reset Signal origin
static int8_t Timer_4_T4RST_Set ( uint8_t res_source, bool up_live ) {
    // Check to see if the Timer 4 is running. To avoid erratic behavior 
    // always and only update the registers when Timer 4 is NOT running.
    if ( ( T4CONbits.ON ) && ( !up_live ) ) {
        // Return with a No Change Flag
        return 0;
    }
    // Check for illegal values
    // Illegal values of T4RST.RSEL
    if ( ( 0x02 == res_source ) || ( 0x0C == res_source ) || 
         ( 0x0D == res_source ) || ( 0x19 <= res_source ) ) {
        // Return a fault code
        return -1;
    }
    // Load the Reset Source value 
    T4RST = res_source;
    // Return to the point of call with success
    return 1;
}

// Return the value of Timer 4 T4RST Register
static uint8_t Timer_4_T4RST_Get ( void ) {
    // Return the value 
    return T4RST;
}

// Configure the Pre - Scaler and Post - Scaler setting of Timer 4
static int8_t Timer_4_T4CON_Set ( uint8_t presc, uint8_t postsc, bool up_live ){
    // Check to see if the Timer 4 is running. To avoid erratic behavior 
    // always and only update the registers when Timer 4 is NOT running.
    if ( ( T4CONbits.ON ) && ( !up_live ) ) {
        // Return with a No Change Flag
        return 0;
    }
    // Check for illegal values
    // Illegal values of T4CON.CKPS
    if ( 0x8F & presc ) {
        // Return with a fault code
        return -1;
    }
    // Illegal values of T4CON.OUTPS
    if ( 0xF0 & postsc ) {
        // Return with a fault code
        return -1;
    }
    // Temporary variables
    uint8_t temp_reg = 0;
    // Combine the given values to set the T4CON Register of Timer 4
    temp_reg = presc | postsc;
    // Update the Timer 4 Control Register
    T4CON = temp_reg;
    // Return to the point of call with success
    return 1;
}

// Return the value of Timer 4 T4CON Register
static uint8_t Timer_4_T4CON_Get ( void ) {
    // Return the value
    return T4CON;
}

// Returns the Enable status of the Interrupt
static bool Timer_4_Get_Inter_Status ( void ) {
    // Returns the enable status of Interrupts
    return PIE8bits.TMR4IE;
}

// Sets the Enable status for the Interrupt
static void Timer_4_Set_Inter_Status ( bool int_en ) {
    // Sets the enable bit of the Interrupts
    PIE8bits.TMR4IE = int_en;
    // Return to the point of call
    return;
}

// Returns the priority of the Interrupt
static bool Timer_4_Get_Inter_Priori ( void ) {
    // Returns the priority set bit of the Interrupt
    return IPR8bits.TMR4IP;
}

// Sets the Enable status for the Interrupt
static void Timer_4_Set_Inter_Priori ( bool int_pr ) {
    // Sets the enable bit of the Interrupts
    IPR8bits.TMR4IP = int_pr;
    // Return to the point of call
    return;
}

/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Interface Functions                                               */
/* ************************************************************************** */
/* ************************************************************************** */

// Return the current value of Timer 4
uint8_t Timer_4_Value_Get ( void ) {
    // Return the value
    return T4TMR;
}

// Set the value of Timer 4
void Timer_4_Value_Set ( uint8_t value ) {
    // Set the value of Timer 4
    T4TMR = value;
    // Return to the point of call
    return;
}

// Return the current value of the Timer 4 Period Register
uint8_t Timer_4_Period_Get ( void ) {
    // Return the value
    return T4PR;
}

// Set the value of Timer 4 Period
void Timer_4_Period_Set ( uint8_t value ) {
    // Set the value of Timer 4 Period
    T4PR = value;
    // Return to the point of call
    return;
}

// Enable the Interrupt
void Timer_4_Interr_ON ( void ) {
    // Enables the Interrupts for Timer 2
    PIE8bits.TMR4IE = 1;
    // Return to the point of call
    return;
}

// Disable the Interrupt
void Timer_4_Interr_OFF ( void ) {
    // Disables the Interrupts for Timer 2
    PIE8bits.TMR4IE = 0;
    // Return to the point of call
    return;
}

// Enable the Interrupt
void Timer_4_Interr_High ( void ) {
    // Set Timer 2 Interrupt Priority High
    IPR8bits.TMR4IP = 0;
    // Return to the point of call
    return;
}

// Enable the Interrupt
void Timer_4_Interr_Low ( void ) {
    // Set Timer 2 Interrupt Priority Low
    IPR8bits.TMR4IP = 1;
    // Return to the point of call
    return;
}

// Start Timer 4. Actual start of counting 
// depends on mode of operation
void Timer_4_Start ( void ) {
    // Set the ON bit of Timer 4 Control Register
    T4CONbits.ON = 1;
    // Return to the point of call
    return;
}

// Stop Timer 4. Effect immediate
void Timer_4_Stop ( void ) {
    // Reset the ON bit of Timer 4 Control Register
    T4CONbits.ON = 0;
    // Return to the point of call
    return;
}

// Return if the Timer 4 is Running or Not
bool Timer_4_Status_Get ( void ) {
    if ( T4CONbits.ON ) {
        // Return that Timer 4 is running
        return true;
    }
    else {
        // Return that Timer 4 is stopped
        return false;
    }
    // Fail safe return
    return false;
}

// Configures the Timer 4 settings.
// Timer 4 has to be stopped before changing any values. Forcing the Timer
// to be stopped can be made externally or by setting force_stop to true.
// Restarting Timer 4 after a successful configuration can done by setting
// force_start flag to true, else Timer 4 has to be started manually.
int8_t Timer_4_Configure ( uint8_t presc, uint8_t postsc, uint8_t clock_source,
                        uint8_t period, uint8_t reset_source, uint8_t mode,
                        uint8_t presc_sync, uint8_t clock_edge,
                        uint8_t start_sync, bool force_stop, 
                        bool force_start, bool int_en, bool int_pr ) {
    // Temporary variables, save status of registers before executing
    int8_t  temp_status = 0;
    uint8_t temp_T4HLT = Timer_4_T4HLT_Get();
    uint8_t temp_T4RST = Timer_4_T4RST_Get();
    uint8_t temp_T4CLK = Timer_4_T4CLK_Get();
    uint8_t temp_T4CON = Timer_4_T4CON_Get();
    bool    temp_st_IE = Timer_4_Get_Inter_Status ( );
    bool    temp_st_IP = Timer_4_Get_Inter_Priori ( );
    // If the force_stop is set to true then stop the Timer before updating
    if ( force_stop ) {
        Timer_4_Stop ( );
    }
    // Check to see if the Timer 4 is running. To avoid erratic behavior 
    // always and only update the registers when Timer 4 is NOT running.
    if ( T4CONbits.ON ) {
        // Return with a No Change Flag
        return 0;
    }
    // Try setting the T4HLT Register
    if ( -1 == Timer_4_T4HLT_Set ( presc_sync, clock_edge, start_sync, 
                                    mode, false ) ) {
        // Store the fault
        temp_status = -1;
    }
    // Try setting the T4RST Register
    if ( -1 == Timer_4_T4RST_Set ( reset_source, false ) ) {
        // Store the fault
        temp_status = -1;
    }
    // Try updating the T4CLK Register
    if ( -1 == Timer_4_T4CLK_Set ( clock_source, false ) ) {
        // Store the fault
        temp_status = -1;
    }
    // Try updating the T4CON Register
    if ( -1 == Timer_4_T4CON_Set ( presc, postsc, false ) ) {
        // Store the fault
        temp_status = -1;
    }
    // If a fault was detected then restore the values of the registers
    // and return to the point of call with a fault code
    if ( 0 > temp_status ) {
        // Store the recalled values
        T4HLT = temp_T4HLT;
        T4RST = temp_T4RST;
        T4CLK = temp_T4CLK;
        T4CON = temp_T4CON;
        // Store the old Interrupt settings
        Timer_4_Set_Inter_Status ( temp_st_IE );
        Timer_4_Set_Inter_Priori ( temp_st_IP );
        // Return with a fault code
        return temp_status;
    }
    // Set the input interrupt settings
    Timer_4_Set_Inter_Status ( int_en );
    Timer_4_Set_Inter_Priori ( int_pr );
    // Set the Timer Period
    Timer_4_Period_Set ( period );
    // Start Timer 4 again if requested
    if ( force_start ) {
        // Start Timer 4
        Timer_4_Start();
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
void __interrupt ( irq ( IRQ_TMR4 ) ) TMR4_Isr ( void )
{
    // Interrupt service routine for CCP1 Module
    // First Reset the Flag
    PIR8bits.TMR4IF = 0;
}

