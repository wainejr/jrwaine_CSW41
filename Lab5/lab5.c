/*__________________________________________________________________________________
|       Disciplina de Sistemas Embarcados - 2022-2
|       Prof. Douglas Renaux
| __________________________________________________________________________________
|
|		Lab 5
| __________________________________________________________________________________
*/

/*
 * @file     lab5.c
 * @author   Joao F. S. Machado & Waine B. O. Junior
 * @brief    Solution to Lab5 of ELF74/CSW41 - UTFPR. \n 
 *           ThreadX example that creates a single thread. \n
             Thread changes the state of LED 1 every 1 second. \n
 * @version  V1
 * @date     Oct, 2022
 *****************************************************************************
*/

/*------------------------------------------------------------------------------
 *
 *      File includes
 *
 *------------------------------------------------------------------------------*/
#include "tx_api.h"
#include "stdbool.h"
#include "stdint.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include "inc/hw_memmap.h"

/*------------------------------------------------------------------------------
 *
 *      Gloval vars declarations
 *
 *------------------------------------------------------------------------------*/

/* Define the ThreadX object control blocks...  */

TX_THREAD               thread_0;
TX_BYTE_POOL            byte_pool_0;

/* Define byte pool memory.  */

UCHAR                   byte_pool_memory[TX_MINIMUM_STACK << 1];

/*------------------------------------------------------------------------------
 *
 *      Functions and Methods
 *
 *------------------------------------------------------------------------------*/

/* Define thread prototype.  */

void    thread_0_entry(ULONG thread_input);


/* Define main entry point.  */

int main()
{
    
    /* Sets the system clock to 120 MHz. */
    SysCtlClockFreqSet((SYSCTL_XTAL_25MHZ | SYSCTL_OSC_MAIN | SYSCTL_USE_PLL | SYSCTL_CFG_VCO_240), 120000000);

    /* Enable GPIO Port N and wait for it to be ready. */
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPION);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPION));
    
    /* Configure pin 1 for use as GPIO output. */
    GPIOPinTypeGPIOOutput(GPIO_PORTN_BASE, GPIO_PIN_1);
    
    /* Enter the ThreadX kernel.  */
    tx_kernel_enter();
}

/* Define what the initial system looks like.  */

void    tx_application_define(void *first_unused_memory)
{

    /* Memory pointer */
    CHAR *pointer = TX_NULL;

    /* Create a byte memory pool from which to allocate the thread stacks.  */
    tx_byte_pool_create(&byte_pool_0, "byte pool 0", byte_pool_memory, TX_MINIMUM_STACK << 1);

    /* Allocate the stack for thread 0.  */
    tx_byte_allocate(&byte_pool_0, (VOID **) &pointer, TX_MINIMUM_STACK, TX_NO_WAIT);

    /* Create the main thread.  */
    tx_thread_create(&thread_0, "thread 0", thread_0_entry, 0, pointer, TX_MINIMUM_STACK, 1, 1, TX_NO_TIME_SLICE, TX_AUTO_START);
}

/* Define the test blink thread.  */

void    thread_0_entry(ULONG thread_input)
{
 
    /* Change the state of the led and sleep for a second. */
    while(1)
    {
        /* Toggles the LED state. */
        GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_1, GPIOPinRead(GPIO_PORTN_BASE, GPIO_PIN_1) ^ GPIO_PIN_1);
        
        /* Sleep for 1 second. */
        tx_thread_sleep(TX_TIMER_TICKS_PER_SECOND);
    }
}