/* This is a small demo of the high-performance ThreadX kernel.  It includes examples of eight
   threads of different priorities, using a message queue, semaphore, mutex, event flags group, 
   byte pool, and block pool. Please refer to Chapter 6 of the ThreadX User Guide for a complete
   description of this demonstration.  */


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
#include "tx_api.h"

#define DEMO_STACK_SIZE         1024
#define DEMO_BYTE_POOL_SIZE     9120

#define CLOCK_FREQ 240000000


/* Define the ThreadX object control blocks...  */

TX_THREAD               thread_0;


/* Define byte pool memory.  */

UCHAR                   byte_pool_memory[DEMO_BYTE_POOL_SIZE];
TX_BYTE_POOL            byte_pool_0;


/* Define event buffer.  */

#ifdef TX_ENABLE_EVENT_TRACE
UCHAR   trace_buffer[0x10000];
#endif


/* Define the counters used in the demo application...  */
ULONG                   thread_0_counter;

/* Define thread prototypes.  */
void    thread_0_entry(ULONG thread_input);


// User Led 1 initialization
void
init_LED_D1(void)
{
    // Enable GPIO Port N (User Leds 1 & 2) peripheral.
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPION);
    
    // Wait for GPIO Port N to be ready.
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPION))
    {
    }
    
    // Configures pin 1 (User Led 1) of the Port N for use as GPIO output.
    GPIOPinTypeGPIOOutput(GPIO_PORTN_BASE, GPIO_PIN_0);
}


void turnOnLED(){
    // Turn on the Led 1.
        GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_0, GPIO_PIN_0);
}

void turnOffLED(){
  
    // Turn off the Led 1.
    GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_0, 0x0);
}


/* Define main entry point.  */
int main()
{
    // Run from the PLL at 240 MHz.
    uint32_t ui32SysClock = SysCtlClockFreqSet((SYSCTL_XTAL_25MHZ |
                                       SYSCTL_OSC_MAIN |
                                       SYSCTL_USE_PLL |
                                       SYSCTL_CFG_VCO_240), CLOCK_FREQ);

    init_LED_D1();
    turnOnLED();
    turnOffLED();
    turnOnLED();
    turnOffLED();

    /* Enter the ThreadX kernel.  */
    tx_kernel_enter();
}


/* Define what the initial system looks like.  */

void    tx_application_define(void *first_unused_memory)
{

CHAR    *pointer = TX_NULL;


#ifdef TX_ENABLE_EVENT_TRACE
    tx_trace_enable(trace_buffer, sizeof(trace_buffer), 32);
#endif

    /* Create a byte memory pool from which to allocate the thread stacks.  */
    tx_byte_pool_create(&byte_pool_0, "byte pool 0", byte_pool_memory, DEMO_BYTE_POOL_SIZE);

    /* Put system definition stuff in here, e.g. thread creates and other assorted
       create information.  */

    /* Allocate the stack for thread 0.  */
    tx_byte_allocate(&byte_pool_0, (VOID **) &pointer, DEMO_STACK_SIZE, TX_NO_WAIT);

    /* Create the main thread.  */
    tx_thread_create(&thread_0, "thread 0", thread_0_entry, 0,  
            pointer, DEMO_STACK_SIZE, 
            1, 1, TX_NO_TIME_SLICE, TX_AUTO_START);
}



/* Define the test threads.  */

void    thread_0_entry(ULONG thread_input)
{

    /* This thread simply sits in while-forever-sleep loop.  */
    while(1)
    {
        /* Increment the thread counter.  */
        thread_0_counter++;

        turnOnLED();        
        
        /* Sleep for 1 second.  */
        tx_thread_sleep(10);
        
        turnOffLED();

    }
}
