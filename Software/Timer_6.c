/* 
 * File:                Timer_6.c
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

#include "Timer_6.h"

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

// Set the mode of operation in the T6HLT Register
static int8_t Timer_6_T6HLT_Set (uint8_t pres_sync, uint8_t pres_edge,
                            uint8_t start_sync, uint8_t mode, bool up_live )
{
    // Check to see if the Timer 6 is running. To avoid erratic behavior 
    // always and only update the registers when Timer 6 is NOT running.
    if((T6CONbits.ON) && (!up_live))
    {
        // Return with a No Change Flag
        return 0;
    }
    // Check for illegal values
    // Illegal values of mode
    if ((0x10 == mode) || (0x14 == mode) || (0x15 == mode) || (0x18 <= mode))
    {
        // Return a fault code
        return -1;
    }
    // Illegal values of T6HLT.PSYNC
    if((T6HLT_PSYNC_ON != pres_sync) || (T6HLT_PSYNC_OFF != pres_sync))
    {
        // Return a fault code
        return -1;
    }
    // Illegal values of T6HLT.CPOL
    if((T6HLT_CKPOL_RISING != pres_edge) || (T6HLT_CKPOL_FALLING != pres_edge))
    {
        // Return a fault code
        return -1;
    }
    // Illegal values of T6HLT.CKSYNC
    if((T6HLT_CKSYNC_ON != start_sync) || (T6HLT_CKSYNC_OFF != start_sync))
    {
        // Return a fault code
        return -1;
    }
    // Temporary variables
    uint8_t temp_reg = 0;
    // Combine the given values to set the T6HLT Register of Timer 6
    temp_reg = pres_sync | pres_edge | start_sync | mode;
    // Update the Timer 6 Hardware Limit Control Register
    T6HLT = temp_reg;
    // Return to the point of call with success
    return 1;
}

// Return the value of Timer 6 T6HLT Register
static uint8_t Timer_6_T6HLT_Get ( void )
{
    // Return the value
    return T6HLT;
}

// Select the clock source for Timer 6
static int8_t Timer_6_T6CLK_Set ( uint8_t clock_source, bool up_live )
{
    // Check to see if the Timer 6 is running. To avoid erratic behavior 
    // always and only update the registers when Timer 6 is NOT running.
    if((T6CONbits.ON) && (!up_live))
    {
        // Return with a No Change Flag
        return 0;
    }
    // Check for illegal values
    // Illegal values of T6CLK.CS
    if(0x0F <= clock_source)
    {
        // Return a fault code
        return -1;
    }
    // Load the clock source value
    T6CLK = clock_source;
    // Return to the point of call with success
    return 1;
}

// Return the value of Timer 6 T6CLK Register
static uint8_t Timer_6_T6CLK_Get ( void )
{
    // Return the value
    return T6CLK;
}

// Select the Timer 6 Reset Signal origin
static int8_t Timer_6_T6RST_Set ( uint8_t res_source, bool up_live )
{
    // Check to see if the Timer 6 is running. To avoid erratic behavior 
    // always and only update the registers when Timer 6 is NOT running.
    if((T6CONbits.ON) && (!up_live))
    {
        // Return with a No Change Flag
        return 0;
    }
    // Check for illegal values
    // Illegal values of T6RST.RSEL
    if((0x03 == res_source) || (0x0C == res_source) || (0x0D == res_source) ||
            0x19 <= res_source)
    {
        // Return a fault code
        return -1;
    }
    // Load the Reset Source value 
    T6RST = res_source;
    // Return to the point of call with success
    return 1;
}

// Return the value of Timer 6 T6RST Register
static uint8_t Timer_6_T6RST_Get ( void )
{
    // Return the value 
    return T6RST;
}

// Configure the Pre - Scaler and Post - Scaler setting of Timer 6
static int8_t Timer_6_T6CON_Set ( uint8_t presc, uint8_t postsc, bool up_live)
{
    // Check to see if the Timer 6 is running. To avoid erratic behavior 
    // always and only update the registers when Timer 6 is NOT running.
    if((T6CONbits.ON) && (!up_live))
    {
        // Return with a No Change Flag
        return 0;
    }
    // Check for illegal values
    // Illegal values of T6CON.CKPS
    if(0x8F & presc)
    {
        // Return with a fault code
        return -1;
    }
    // Illegal values of T6CON.OUTPS
    if(0xF0 & postsc)
    {
        // Return with a fault code
        return -1;
    }
    // Temporary variables
    uint8_t temp_reg = 0;
    // Combine the given values to set the T6CON Register of Timer 6
    temp_reg = presc | postsc;
    // Update the Timer 6 Control Register
    T6CON = temp_reg;
    // Return to the point of call with success
    return 1;
}

// Return the value of Timer 6 T6CON Register
static uint8_t Timer_6_T6CON_Get ( void )
{
    // Return the value
    return T6CON;
}
/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Interface Functions                                               */
/* ************************************************************************** */
/* ************************************************************************** */

// Return the current value of Timer 6
uint8_t Timer_6_Value_Get ( void )
{
    // Return the value
    return T6TMR;
}

// Set the value of Timer 6
void Timer_6_Value_Set ( uint8_t value )
{
    // Set the value of Timer 6
    T6TMR = value;
    // Return to the point of call
    return;
}

// Return the current value of the Timer 6 Period Register
uint8_t Timer_6_Period_Get ( void )
{
    // Return the value
    return T6PR;
}

// Set the value of Timer 6 Period
void Timer_6_Period_Set ( uint8_t value )
{
    // Set the value of Timer 6 Period
    T6PR = value;
    // Return to the point of call
    return;
}

// Start Timer 6. Actual start of counting 
// depends on mode of operation
void Timer_6_Start ( void )
{
    // Set the ON bit of Timer 6 Control Register
    T6CONbits.ON = 1;
    // Return to the point of call
    return;
}

// Stop Timer 6. Effect immediate
void Timer_6_Stop ( void )
{
    // Reset the ON bit of Timer 6 Control Register
    T6CONbits.ON = 0;
    // Return to the point of call
    return;
}

// Return if the Timer 6 is Running or Not
bool Timer_6_Status_Get ( void )
{
    if(T6CONbits.ON)
    {
        // Return that Timer 6 is running
        return true;
    }
    else
    {
        // Return that Timer 6 is stopped
        return false;
    }
    // Fail safe return
    return false;
}

// Configures the Timer 6 settings.
// Timer 6 has to be stopped before changing any values. Forcing the Timer
// to be stopped can be made externally or by setting force_stop to true.
// Restarting Timer 6 after a successful configuration can done by setting
// force_start flag to true, else Timer 6 has to be started manually.
int8_t Timer_6_Configure ( uint8_t presc, uint8_t postsc, uint8_t clock_source,
        uint8_t reset_source, uint8_t mode, uint8_t presc_sync,
        uint8_t clock_edge, uint8_t start_sync, bool force_stop, 
        bool force_start)
{
    // Temporary variables, save status of registers before executing
    int8_t temp_status = 0;
    uint8_t temp_T6HLT = Timer_6_T6HLT_Get();
    uint8_t temp_T6RST = Timer_6_T6RST_Get();
    uint8_t temp_T6CLK = Timer_6_T6CLK_Get();
    uint8_t temp_T6CON = Timer_6_T6CON_Get();
    // If the force_stop is set to true then stop the Timer before updating
    if(force_stop)
    {
        Timer_6_Stop();
    }
    // Check to see if the Timer 6 is running. To avoid erratic behavior 
    // always and only update the registers when Timer 6 is NOT running.
    if(T6CONbits.ON)
    {
        // Return with a No Change Flag
        return 0;
    }
    // Try setting the T6HLT Register
    if(-1 == Timer_6_T6HLT_Set(presc_sync, clock_edge, start_sync, mode, false))
    {
        // Store the fault
        temp_status = -1;
    }
    // Try setting the T6RST Register
    if(-1 == Timer_6_T6RST_Set(reset_source, false))
    {
        // Store the fault
        temp_status = -1;
    }
    // Try updating the T6CLK Register
    if(-1 == Timer_6_T6CLK_Set(clock_source, false))
    {
        // Store the fault
        temp_status = -1;
    }
    // Try updating the T6CON Register
    if(-1 == Timer_6_T6CON_Set(presc, postsc, false))
    {
        // Store the fault
        temp_status = -1;
    }
    // If a fault was detected then restore the values of the registers
    // and return to the point of call with a fault code
    if(0 > temp_status)
    {
        // Store the recalled values
        T6HLT = temp_T6HLT;
        T6RST = temp_T6RST;
        T6CLK = temp_T6CLK;
        T6CON = temp_T6CON;
        // Return with a fault code
        return temp_status;
    }
    // Start Timer 6 again if requested
    if(force_start)
    {
        // Start Timer 6
        Timer_6_Start();
    }
    // Return to the point of call
    return 1;
}