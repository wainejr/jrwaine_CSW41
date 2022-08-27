//*****************************************************************************
//
// project0.c - Example to demonstrate minimal TivaWare setup
//
// Copyright (c) 2012-2020 Texas Instruments Incorporated.  All rights reserved.
// Software License Agreement
// 
// Texas Instruments (TI) is supplying this software for use solely and
// exclusively on TI's microcontroller products. The software is owned by
// TI and/or its suppliers, and is protected under applicable copyright
// laws. You may not combine this software with "viral" open-source
// software in order to form a larger program.
// 
// THIS SOFTWARE IS PROVIDED "AS IS" AND WITH ALL FAULTS.
// NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT
// NOT LIMITED TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. TI SHALL NOT, UNDER ANY
// CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR CONSEQUENTIAL
// DAMAGES, FOR ANY REASON WHATSOEVER.
// 
// This is part of revision 2.2.0.295 of the EK-TM4C1294XL Firmware Package.
//
//*****************************************************************************

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/systick.h"
#include "driverlib/timer.h"

#define MAX_SYSTICK 16777216

//*****************************************************************************
//
//! \addtogroup example_list
//! <h1>Project Zero (project0)</h1>
//!
//! This example demonstrates the use of TivaWare to setup the clocks and
//! toggle GPIO pins to make the LED blink. This is a good place to start
//! understanding your launchpad and the tools that can be used to program it.
//
//*****************************************************************************

volatile uint32_t ui32TimerValue = 0;

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

    // Enable GPIO Port J (User Switchs 1 & 2) peripheral.
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOJ);
    
    // Enable TIMER 0 peripheral.
    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);
    
    // Enable GPIO Port N (User Leds 1 & 2) peripheral.
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPION);
    
    // Wait for GPIO Port J to be ready.
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOJ));
    
    // Configure the user switch 1.
    
    // Configures pin 0 (User Switch 1) of the Port J for use as GPIO input.
    GPIOPinTypeGPIOInput(GPIO_PORTJ_BASE, GPIO_PIN_0);
    
    // Set the pull up resistor to 2 amps on pin 0 of the Port J.
    GPIOPadConfigSet(GPIO_PORTJ_BASE, GPIO_PIN_0, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);
    
    // Sets the interrupt type for the rising edge on pin 0 of the Port J.
    GPIOIntTypeSet(GPIO_PORTJ_BASE, GPIO_PIN_0, GPIO_RISING_EDGE);
    
    // Registers an interrupt handler for the GPIO port J.
    GPIOIntRegister(GPIO_PORTJ_BASE, PortJIntHandler);
    
    // Wait for TIMER 0 to be ready.
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_TIMER0));
    
    // Configure the timer 0.
    
    // Set the timer to 0 in one shot mode counting up full-width.
    TimerConfigure(TIMER0_BASE, TIMER_CFG_ONE_SHOT_UP);
    
    // Sets timer matching value to 3 times the frequency value (3 seconds)
    TimerMatchSet(TIMER0_BASE, TIMER_A, ui32SysClock * 3);
    
    // Registers an interrupt handler for Timer 0.
    TimerIntRegister(TIMER0_BASE, TIMER_A, Timer0IntHandler);
    
    // Enable interrupt source for timer 0 in timer match mode.
    TimerIntEnable(TIMER0_BASE, TIMER_TIMA_MATCH);  
    
    // Wait for GPIO Port N to be ready.
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPION));
    
     // Configure the user led 1.
    
    // Configures pin 1 (User Led 1) of the Port N for use as GPIO output.
    GPIOPinTypeGPIOOutput(GPIO_PORTN_BASE, GPIO_PIN_1);
    
    // Configure the SysTick.
    
    // Sets the SysTick counter period to its maximum value (2^32).
    SysTickPeriodSet(MAX_SYSTICK);  
    
    // Enables the SysTick interrupt.
    SysTickIntEnable();
    
    // Enables the SysTick counter.
    SysTickEnable();
    
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
