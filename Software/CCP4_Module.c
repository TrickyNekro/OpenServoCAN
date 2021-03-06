/* 
 * File:                CCP4_Module.c
 * Author:              Provatos Eleftherios
 * Comments:            For use with PIC18F26K83 in OpenServoCAN project
 * Revision history:    V1.00
 */

/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
/* ************************************************************************** */

#include "CCP4_Module.h"

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

// Set how the data are adjusted in the value register 
// ONLY when working in PWM Mode
static int8_t CCP4_Module_Data_Adjustment ( bool left_adj )
{
    // Check for the data adjustment
    if( left_adj )
    {
        CCP4_CCP4CON_LEFT_ADJUST_DATA();
    }
    else
    {
        CCP4_CCP4CON_RIGHT_ADJUST_DATA();
    }
    // Return to the point of call
    return 1;
}

// Set the Mode in which the module is working
static int8_t CCP4_Module_Set_Mode ( uint8_t mode )
{
    // Check to see if the Data are in the correct range
    if( mode & ~CCP4_CCP4CON_MODE_MASK )
    {
        // Data Input scope is out of range, return error
        return -1;
    }
    // Reset the mode register
    CCP4CON &= ~CCP4_CCP4CON_MODE_MASK;
    // Set the mode according to the request
    CCP4CON |= mode;
    // Return with Success
    return 1;
}

// Set the Input to be captured by the module
static int8_t CCP4_Module_Set_Capt_Input ( uint8_t input )
{
    // Check to see if the Data are in the correct range
    if( input & ~CCP4_CCP4CAP_CTS_MASK )
    {
        // Data Input scope is out of range, return error
        return -1;
    }
    // Reset the Capture Input Register
    CCP4CAP &= ~CCP4_CCP4CAP_CTS_MASK;
    // Set the Capture Input according to the request
    CCP4CAP |= input;
    // Return with Success
    return 1;
}

// Set the Timer the Capture Module is based on.
static int8_t CCP4_Module_Set_Timer ( uint8_t timer_sel )
{
    // Check to see if the Data are in the correct range
    if( ( timer_sel & ~CCP4_CCPTMRS0_C4TSEL_MASK ) || ( 0 == timer_sel ) )
    {
        // Data Input scope is out of range, return error
        return -1;        
    }
    // Reset the Timer Input
    CCPTMRS0 &= ~CCP4_CCPTMRS0_C4TSEL_MASK;
    // Set the Timer connected with the module
    CCPTMRS0 |= timer_sel;
    // Return with Success
    return 1;
}

/* ************************************************************************** */
/* ************************************************************************** */
// Section: Interface Functions                                               */
/* ************************************************************************** */
/* ************************************************************************** */

// Configures the CCP1 Module
// Always Disable the CCP1 Module before configuration
// Configures mode of operation
// Configures the data adjustment
// Configures the Module Capture Input
int8_t CCP4_Module_Config ( uint8_t mode, uint8_t timer_sel, uint8_t capt_in,
                             bool left_adj, bool int_en, bool int_hi_pri, bool en )
{
    // Temporary variables
    int8_t temp_status = 0;
    // First check to see if the module is disabled
    if( CCP4CON & CCP4_CCP4CON_EN_MASK )
    {
        // Return that zero changed occurred 
        // due to the module being operational
        return 0;
    }
    // Configure the Mode the device should work in
    temp_status += CCP4_Module_Set_Mode( mode );
    // Configure the Timer that should operate with the Comparator
    temp_status += CCP4_Module_Set_Timer( timer_sel );
    // Configure the capture input to be used
    temp_status += CCP4_Module_Set_Capt_Input( capt_in );
    // Configure the Data Alignment
    if ( left_adj )
    {
        // Data are Left adjusted
        CCP4_CCP4CON_LEFT_ADJUST_DATA();
    }
    else
    {
        // Data are Right adjusted
        CCP4_CCP4CON_RIGHT_ADJUST_DATA();
    }
    // Configure the Interrupt states
    if ( int_en )
    {
        // Clear the Interrupt Flag
        CCP4_CLEAR_INTERRUPT_FLAG();
        // Enable the Interrupt
        CCP4_ENABLE_INTERRUPT();
    }
    else
    {
        // Disable the Interrupt
        CCP4_DISABLE_INTERRUPT();
    }
    // Configure the Interrupt priority
    if ( int_hi_pri )
    {
        // Interrupt set to high priority
        CCP4_INTERRUPT_SET_HIGH_PRIORITY();
    }
    else
    {
        // Interrupt set to low priority
        CCP4_INTERRUPT_SET_LOW_PRIORITY();
    }
    // Check to see the state of configuration
    if( 3 > temp_status )
    {
        // Then the First 3 Configurations failed,
        // return error
        return -1;
    }
    // If not everything was configured correctly so
    // continue with enabling or not the module
    if ( en )
    {
        // Enable as a last step the module
        CCP4_CCP4CON_ENABLE_MODULE();
    }
    // Return to the point of call with success
    return 1;
}

// Enables the Module, 
// Returns the State of the Register
uint8_t CCP4_Module_Enable ( bool en )
{
    // Check the enable status
    if( en )
    {   
        // Enable the CCP1 Module
        CCP4_CCP4CON_ENABLE_MODULE();   
    }
    else
    {
        // Enable the CCP1 Module
        CCP4_CCP4CON_DISABLE_MODULE();
    }
    // Return the state of the configuration register
    return CCP4CON;
}

// Return an output based on the Enable
// bit of the comparator.
// Returns TRUE for SET / ENABLED Module.
// Returns HALSE for RESET / DISABLED Module.
bool CCP4_Module_Get_EN_State ( void )
{
    // Check to see the EN bit state
    if( CCP4CON & CCP4_CCP4CON_EN_MASK )
    {
        // EN is set
        return true;
    }
    else
    {
        // EN is Reset
        return false;
    }
    // Fail-Safe Return
    return false;
}

// Return an output based on the output 
// state of the comparator. 
// Returns TRUE for SET / HIGH output.
// Returns FALSE for RESET / LOW output.
// Does NOT perform any check.
bool CCP4_Module_Get_OUT_State ( void )
{
    // Check to see the OUT bit state
    if( CCP4CON & CCP4_CCP4CON_OUT_MASK )
    {
        // OUT is Set
        return true;
    }
    else
    {
        // OUT is Reset
        return false;
    }
    // Fail-Safe Return
    return false;
}

// Return an output based on the Data 
// Alignment of the comparator. 
// Returns TRUE for SET / LEFT Alignment.
// Returns FALSE for RESET / RIGHT Alignment.
// Does NOT perform any check.
bool CCP4_Module_Get_Data_Align ( void )
{
    // Check to see the OUT bit state
    if( CCP4CON & CCP4_CCP4CON_FMT_MASK )
    {
        // Data are left aligned
        return true;
    }
    else
    {
        // Data are right aligned
        return false;
    }
    // Fail-Safe Return
    return false;
}

// Returns the mode that the comparator
// is set in. Does NOT perform any check.
uint8_t CCP4_Module_Get_Mode ( void )
{
    // Returns the MODE bits of CCP1CON
    return ( CCP4CON & CCP4_CCP4CON_MODE_MASK );
}

// Returns the Value of the Comparator
// Checks for the Mode the comparator is working in
// and the output depends on it.
uint16_t CCP4_Module_Get_Value ( void )
{
    // Temporary Variables
    uint16_t temp_HIGH = CCPR4H;
    uint16_t temp_LOW  = CCPR4L;
    // Check the mode the comparator is in,
    // If it is in PWM Mode return the Comparator
    // value according to the Left / Right Adjust.
    // If not return the whole CCPR value.
    if ( 0x0C <= ( CCP4CON & CCP4_CCP4CON_MODE_MASK ) )
    {
        // The Comparator is in PWM mode, check FMT
        if ( CCP4CON & CCP4_CCP4CON_FMT_MASK )
        {
            // Data are Left adjusted
            return ((temp_HIGH << 2) | (temp_LOW >> 6));
        }
        else
        {
            // Data are Right adjusted
            return ((temp_HIGH << 8) | temp_LOW);
        }
    }
    else
    {
        // The Comparator is in any other mode,
        // so just combine High and Low Byte
        return ((temp_HIGH << 8) | temp_LOW);
    }
    // Fail-Safe Return
    return ((temp_HIGH << 8) | temp_LOW);
}

// Set the value of the comparator
// Checks the mode comparator is in before loading.
int8_t CCP4_Module_Set_Value ( uint16_t value )
{
    // Temporary Variables
    uint8_t loader_low = 0, loader_high = 0;
    // Check the mode the comparator is in,
    // If it is in PWM Mode return the Comparator
    // value according to the Left / Right Adjust.
    // If not return the whole CCPR value.
    if ( 0x0C <= ( CCP4CON & CCP4_CCP4CON_MODE_MASK ) )
    {
        // If it is in PWM mode the value entered 
        // should not be greater than 1023. If it is
        // then return an error
        if ( value > 0x3FF )
        {
            // Value will overflow, return error
            return -1;
        }
        // Start loading the value according to alignment.
        if ( CCP4CON & CCP4_CCP4CON_FMT_MASK )
        {
            // Data are Left Adjusted
            // Load the High Byte
            CCPR4H = ( value >> 2 ) & 0xFF;
            // Load the Low Byte
            CCPR4L = ( value << 6 ) & 0xFF;
            // Return to the point of call
            return 1;
        }   
        else
        {
            // Data are Right Adjusted
            // Load the High Byte
            CCPR4H = ( value >> 8 ) & 0xFF;
            // Load the Low Byte
            CCPR4L = ( value >> 0 ) & 0xFF;
            // Return to the point of call
            return 1;
        }
    }    
    else
    {
        // The Comparator is in any other mode,
        // so just load High and Low Byte.
        // Load the High Byte
        CCPR4H = ( value >> 8 ) & 0xFF;
        // Load the Low Byte
        CCPR4L = ( value >> 0 ) & 0xFF;
        // Return to the point of call
        return 1;
    }
    // Fail-Safe Return
    return 0;
}

/* ************************************************************************** */
/* ************************************************************************** */
// Section: Interrupt Functions                                               */
/* ************************************************************************** */
/* ************************************************************************** */

// Any Priority Interrupt Vector for Vectored Interrupts MVECEN = ON
void __interrupt( irq( IRQ_CCP4 ) ) CCP4_Isr ( void )
{
    // Interrupt service routine for CCP1 Module
    // First Reset the Flag
    PIR9bits.CCP4IF = 0;
}

