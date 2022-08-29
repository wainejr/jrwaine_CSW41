/*__________________________________________________________________________________
|       Disciplina de Sistemas Embarcados - 2022-1
|       Prof. Douglas Renaux
| __________________________________________________________________________________
|
|		Lab 2
| __________________________________________________________________________________
*/

/**
 * @file     blinky.c
 * @author   Joao F. S. Machado & Waine B. O. Junior
 * @date     Aug, 2022
 ******************************************************************************/

/*------------------------------------------------------------------------------
 *
 *      File includes
 *
 *------------------------------------------------------------------------------*/
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/sysctl.h"
#include "driverlib/systick.h"
#include "driverlib/timer.h"
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"

/*------------------------------------------------------------------------------
 *
 *      Global Typedefs, constants and defines
 *
 *------------------------------------------------------------------------------*/
// Define Max Value for SysTick.
#define MAX_SYSTICK 16777216

/*------------------------------------------------------------------------------
 *
 *      Gloval vars declarations
 *
 *------------------------------------------------------------------------------*/
// Global variable to store timer time.
volatile uint32_t ui32TimerValue;

//*****************************************************************************
//
// The error routine that is called if the driver library encounters an error.
//
//*****************************************************************************
#ifdef DEBUG
void
__error__(char *pcFilename, uint32_t ui32Line)
{
}
#endif

/*------------------------------------------------------------------------------
 *
 *      Functions and Methods
 *
 *------------------------------------------------------------------------------*/

// SysTick Interrupt handler
void
SysTickHandler(void)
{
    // Disables the SysTick counter
    SysTickDisable();
    
    // Turn on the User Led 1.
    GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_1, GPIO_PIN_1);
    
    // Enables the TIMER 0.
    TimerEnable(TIMER0_BASE, TIMER_A);
    
    // Enables the GPIO Port J interrupts.
    GPIOIntEnable(GPIO_PORTJ_BASE, GPIO_INT_PIN_0);
}

// Port J Interrupt handler
void
PortJIntHandler(void)
{   
    // Disables the TIMER 0.
    TimerDisable(TIMER0_BASE, TIMER_A);
    
    // Gets the current TIMER 0 value.
    ui32TimerValue = TimerValueGet(TIMER0_BASE, TIMER_A);
    
    // Removes the interrupt handler for the GPIO Port J and disables the GPIO port J interrupt in the interrupt controller.
    GPIOIntUnregister(GPIO_PORTJ_BASE);
    
    // Removes the interrupt handler for the TIMER 0 and disables the TIMER 0 interrupt in the interrupt controller.
    TimerIntUnregister(TIMER0_BASE, TIMER_A);
    
    // Turn off the User Led 1.
    GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_1, 0x0);
}

// Timer Interrupt handler
void
Timer0IntHandler(void)
{   
    // Disables the TIMER 0.
    TimerDisable(TIMER0_BASE, TIMER_A);
    
    // Gets the current TIMER 0 value.
    ui32TimerValue = TimerValueGet(TIMER0_BASE, TIMER_A);
    
    // Removes the interrupt handler for the GPIO Port J and disables the GPIO port J interrupt in the interrupt controller.
    GPIOIntUnregister(GPIO_PORTJ_BASE);
    
    // Removes the interrupt handler for the TIMER 0 and disables the TIMER 0 interrupt in the interrupt controller.
    TimerIntUnregister(TIMER0_BASE, TIMER_A);
    
    // Turn off the User Led 1.
    GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_1, 0x0);
}

// User Switch 1 initialization
void
init_SW_1(void)
{
    // Enable GPIO Port J (User Switchs 1 & 2) peripheral.
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOJ);
    
    // Wait for GPIO Port J to be ready.
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOJ));
    
    // Configures pin 0 (User Switch 1) of the Port J for use as GPIO input.
    GPIOPinTypeGPIOInput(GPIO_PORTJ_BASE, GPIO_PIN_0);
    
    // Set the pull up resistor to 2 amps on pin 0 of the Port J.
    GPIOPadConfigSet(GPIO_PORTJ_BASE, GPIO_PIN_0, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);
    
    // Sets the interrupt type for the rising edge on pin 0 of the Port J.
    GPIOIntTypeSet(GPIO_PORTJ_BASE, GPIO_PIN_0, GPIO_RISING_EDGE);
    
    // Enable interrupt source for GPIO Port J pin 0 (User Switch 1).
    GPIOIntEnable(GPIO_PORTJ_BASE, GPIO_INT_PIN_0);
    
    // Registers an interrupt handler for the GPIO port J.
    IntEnable(INT_GPIOJ);
}

// User Led 1 initialization
void
init_LED_D1(void)
{
    // Enable GPIO Port N (User Leds 1 & 2) peripheral.
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPION);
    
    // Wait for GPIO Port N to be ready.
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPION));
    
    // Configures pin 1 (User Led 1) of the Port N for use as GPIO output.
    GPIOPinTypeGPIOOutput(GPIO_PORTN_BASE, GPIO_PIN_1);
}

// Timer 0 A initialization
void
init_Timer_0A(uint32_t ui32SysClock, uint32_t seconds)
{
    // Enable TIMER 0 peripheral.
    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);
    
    // Wait for TIMER 0 to be ready.
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_TIMER0));
    
    // Set the timer to 0 in one shot mode counting up full-width.
    TimerConfigure(TIMER0_BASE, TIMER_CFG_ONE_SHOT_UP);
    
    // Sets timer matching value to 3 times the frequency value (3 seconds).
    TimerMatchSet(TIMER0_BASE, TIMER_A, ui32SysClock * seconds);
    
    // Enable interrupt source for timer 0 in timer match mode.
    TimerIntEnable(TIMER0_BASE, TIMER_TIMA_MATCH);  
    
    // Registers an interrupt handler for Timer 0.
    IntEnable(INT_TIMER0A);
}

// SysTick initialization
void
init_SysTick(void)
{
    // Sets the SysTick counter period to its maximum value (2^32).
    SysTickPeriodSet(MAX_SYSTICK);  
    
    // Enables the SysTick interrupt.
    SysTickIntEnable();
    
    // Enables the SysTick counter.
    SysTickEnable();
}

//*****************************************************************************
//
// Main 'C' Language entry point.
//
//*****************************************************************************
int
main(void)
{
    // Run from the PLL at 120 MHz.
    uint32_t ui32SysClock = SysCtlClockFreqSet((SYSCTL_XTAL_25MHZ |
                                       SYSCTL_OSC_MAIN |
                                       SYSCTL_USE_PLL |
                                       SYSCTL_CFG_VCO_240), 120000000);
    
    // configure the User Switch 1.
    init_SW_1();
    
    // configure the User Led D1.
    init_LED_D1();
    
    // Configure the Timer 0A to count 3 seconds.
    init_Timer_0A(ui32SysClock, 3);
    
    // Configure and enable the systick.
    init_SysTick();
    
    // Sets the count reference value.
    ui32TimerValue = 0;
    
    // Busy waiting on timer value.
    while(1)
    {
        if(ui32TimerValue)
        {
            // Prints the value in clocks and the corresponding value in milliseconds.
            printf("%d clocks\n", ui32TimerValue);
            printf("%d ms\n", ui32TimerValue/(ui32SysClock/1000));
            break;
        }
    }
}
