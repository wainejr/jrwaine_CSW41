/**
 * @file     main_threadx.c
 * @author   Joao F. S. Machado & Waine B. O. Junior
 * @brief    Final project of ELF74/CSW41 - UTFPR. \n
 * @version  V1
 * @date     Dec, 2022
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

#include "drivers/all.h"

/*------------------------------------------------------------------------------
 *
 *      Gloval vars declarations
 *
 *------------------------------------------------------------------------------*/

#define BYTE_POOL_SIZE     TX_MINIMUM_STACK << 4
#define SCHEDULING         5

#define THREAD_1_INPUT     (300*TX_TIMER_TICKS_PER_SECOND)/1000
#define THREAD_2_INPUT     (500*TX_TIMER_TICKS_PER_SECOND)/1000
#define THREAD_3_INPUT     (800*TX_TIMER_TICKS_PER_SECOND)/1000

/* Define the ThreadX object control blocks...  */

TX_THREAD               thread_1;
TX_THREAD               thread_2;
TX_THREAD               thread_3;
TX_BYTE_POOL            byte_pool_0;
TX_MUTEX                mutex_0;
TX_TIMER                timer_1;
TX_TIMER                timer_2;
TX_TIMER                timer_3;

/* Define byte pool memory.  */

UCHAR                   byte_pool_memory[BYTE_POOL_SIZE];

/*------------------------------------------------------------------------------
 *
 *      Functions and Methods
 *
 *------------------------------------------------------------------------------*/

/* Define thread prototypes.  */

void    thread_1_entry(ULONG reload);
void    thread_2_entry(ULONG reload);
void    thread_3_entry(ULONG reload);
void    thread_1_m_entry(ULONG reload);
void    thread_3_m_entry(ULONG reload);

/* Define timer prototype.  */

void    timer_expiration_1(ULONG expiration_input);
void    timer_expiration_2(ULONG expiration_input);
void    timer_expiration_3(ULONG expiration_input);

/* Define main entry point.  */

void test_joystick(){
    while(true){
      int val_x = drivers::get_joystick_x();
      int val_y = drivers::get_joystick_y();
      misc::Vector<int> pos = drivers::get_joystick_pos();
      printf("x y %d %d pos (%d %d)\n", val_x, val_y, pos.x, pos.y);
    }
}

int main()
{
    /* Sets the system clock to 120 MHz. */
    SysCtlClockFreqSet((SYSCTL_XTAL_25MHZ | SYSCTL_OSC_MAIN | SYSCTL_USE_PLL | SYSCTL_CFG_VCO_240), 120000000);
    drivers::setup_all();
    
    /* Enable GPIO Port N and wait for it to be ready. */
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPION);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPION));
    
    /* Configure pin 1 (User LED 1) and pin 0 (User LED 2) for use as GPIO output. */
    GPIOPinTypeGPIOOutput(GPIO_PORTN_BASE, GPIO_PIN_1 | GPIO_PIN_0);
    
    /* Enable GPIO Port F and wait for it to be ready. */
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF));
    
    /* Configure pin 4 (User LED 3) for use as GPIO output. */
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_4);
    
    /* Enter the ThreadX kernel.  */
    tx_kernel_enter();
}

/* Define the initial system for scheduling 5. */

void tx_application_define_5()
{
    /* Memory pointer */
    CHAR *pointer = (CHAR*)TX_NULL;

    /* Create a byte memory pool from which to allocate the thread stacks.  */
    tx_byte_pool_create(&byte_pool_0, "byte pool 0", byte_pool_memory, BYTE_POOL_SIZE);

    /* Allocate the stack for thread 1.  */
    tx_byte_allocate(&byte_pool_0, (VOID **) &pointer, TX_MINIMUM_STACK, TX_NO_WAIT);

    /* Create the thread 1.  */
    tx_thread_create(&thread_1, "thread 1", thread_1_m_entry, THREAD_1_INPUT, pointer, TX_MINIMUM_STACK, 5, 5, TX_NO_TIME_SLICE, TX_AUTO_START);
    
    /* Allocate the stack for thread 2.  */
    tx_byte_allocate(&byte_pool_0, (VOID **) &pointer, TX_MINIMUM_STACK, TX_NO_WAIT);

    /* Create the thread 2.  */
    tx_thread_create(&thread_2, "thread 2", thread_2_entry, THREAD_2_INPUT, pointer, TX_MINIMUM_STACK, 15, 15, TX_NO_TIME_SLICE, TX_AUTO_START);
    
    /* Allocate the stack for thread 3.  */
    tx_byte_allocate(&byte_pool_0, (VOID **) &pointer, TX_MINIMUM_STACK, TX_NO_WAIT);

    /* Create the thread 3.  */
    tx_thread_create(&thread_3, "thread 3", thread_3_m_entry, THREAD_3_INPUT, pointer, TX_MINIMUM_STACK, 25, 25, TX_NO_TIME_SLICE, TX_AUTO_START);
    
    /* Create the mutex used by thread 1 and 3 with priority inheritance. */
    tx_mutex_create(&mutex_0, "mutex 0", TX_INHERIT);
}

/* Define what the initial system looks like.  */

void    tx_application_define(void *first_unused_memory)
{
    tx_application_define_5();

    /* Create the timer 1. */
    tx_timer_create(&timer_1, "timer 1", timer_expiration_1, 1, TX_TIMER_TICKS_PER_SECOND * 1, TX_TIMER_TICKS_PER_SECOND * 1, TX_AUTO_ACTIVATE);
    
    /* Create the timer 2. */
    tx_timer_create(&timer_2, "timer 2", timer_expiration_2, 2, TX_TIMER_TICKS_PER_SECOND * 1.5, TX_TIMER_TICKS_PER_SECOND * 1.5, TX_AUTO_ACTIVATE);
    
    /* Create the timer 3. */
    tx_timer_create(&timer_3, "timer 3", timer_expiration_3, 3, TX_TIMER_TICKS_PER_SECOND * 4, TX_TIMER_TICKS_PER_SECOND * 4, TX_AUTO_ACTIVATE);
    
    /* Set internal system clock to zero */
    tx_time_set(0x0);
}

/* Define the thread 1.  */

void    thread_1_entry(ULONG reload)
{
    /* Stores previous and current system time value */
    ULONG previous, current;
    
    /* Stores the iterator value */
    volatile ULONG iterations = reload;
    
    /* Loop forever */
    while(1)
    {   
        /* Takes the time at the start of the job */
        previous = tx_time_get();
        
        /* Each cycle takes about 58 clocks */
        while(iterations)
        {
            /* Turn on Led 1 */
            GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_1, GPIO_PIN_1);
            
            /* Turn off Leds 1, 2 and 3  */
            GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_1 | GPIO_PIN_0, 0x0);
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_4, 0x0);
            
            /* Pickup the current system time */
            current = tx_time_get();
            
            /* If only one tick has passed, decrement the iterations, if not, just update the previous value */
            if((previous + 1) == current)
            {
                previous = current;
                iterations--;
            }
            else if(previous != current)
            {
                previous = current;
            }
        }
        
         /* Reload the execution cycles */
        iterations = reload;
        
        /* Suspend thread 1 */
        tx_thread_suspend(&thread_1);
    }
}

/* Define the thread 3.  */

void    thread_3_entry(ULONG reload)
{
    /* Stores previous and current system time value */
    ULONG previous, current;
    
    /* Stores the iterator value */
    volatile ULONG iterations = reload;
    
    /* Loop forever */
    while(1)
    {   
        /* Takes the time at the start of the job */
        previous = tx_time_get();
        
        /* Each cycle takes about 58 clocks */
        while(iterations)
        {
            /* Turn on Led 1 */
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_4, GPIO_PIN_4);
            
            /* Turn off Leds 1, 2 and 3  */
            GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_1 | GPIO_PIN_0, 0x0);
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_4, 0x0);
            
            /* Pickup the current system time */
            current = tx_time_get();
            
            /* If only one tick has passed, decrement the iterations, if not, just update the previous value */
            if((previous + 1) == current)
            {
                previous = current;
                iterations--;
            }
            else if(previous != current)
            {
                previous = current;
            }
        }
        
         /* Reload the execution cycles */
        iterations = reload;
        
        /* Suspend thread 3 */
        tx_thread_suspend(&thread_3);
    }
}

/* Define the thread 2.  */

void    thread_2_entry(ULONG reload)
{
    /* Stores previous and current system time value */
    ULONG previous, current;
    
    /* Stores the iterator value */
    volatile ULONG iterations = reload;
    
    /* Loop forever */
    while(1)
    {   
        /* Takes the time at the start of the job */
        previous = tx_time_get();
        
        /* Each cycle takes about 58 clocks */
        while(iterations)
        {
            /* Turn on Led 1 */
            GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_0, GPIO_PIN_0);
            
            /* Turn off Leds 1, 2 and 3  */
            GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_1 | GPIO_PIN_0, 0x0);
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_4, 0x0);
            
            /* Pickup the current system time */
            current = tx_time_get();
            
            /* If only one tick has passed, decrement the iterations, if not, just update the previous value */
            if((previous + 1) == current)
            {
                previous = current;
                iterations--;
            }
            else if(previous != current)
            {
                previous = current;
            }
        }
        
         /* Reload the execution cycles */
        iterations = reload;
        
        /* Suspend thread 2 */
        tx_thread_suspend(&thread_2);
    }
}

/* Define the thread 1 mutex.  */

void    thread_1_m_entry(ULONG reload)
{
    /* Stores previous and current system time value */
    ULONG previous, current;
    
    /* Stores the iterator value */
    volatile ULONG iterations = reload;
    
    /* Loop forever */
    while(1)
    {   
        /* Takes the time at the start of the job */
        previous = tx_time_get();
        
        /* Get Mutex */
        tx_mutex_get(&mutex_0, TX_WAIT_FOREVER);

        /* Each cycle takes about 58 clocks */
        while(iterations)
        {
            /* Turn on Led 1 */
            GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_1, GPIO_PIN_1);
            
            /* Turn off Leds 1, 2 and 3  */
            GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_1 | GPIO_PIN_0, 0x0);
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_4, 0x0);
            
            /* Pickup the current system time */
            current = tx_time_get();
            
            /* If only one tick has passed, decrement the iterations, if not, just update the previous value */
            if((previous + 1) == current)
            {
                previous = current;
                iterations--;
            }
            else if(previous != current)
            {
                previous = current;
            }
        }
        
         /* Reload the execution cycles */
        iterations = reload;
        
        /* Put Mutex */
        tx_mutex_put(&mutex_0);
        
        /* Suspend thread 1 */
        tx_thread_suspend(&thread_1);
    }
}

/* Define the thread 3 mutex.  */

void    thread_3_m_entry(ULONG reload)
{
    /* Stores previous and current system time value */
    ULONG previous, current;
    
    /* Stores the iterator value */
    volatile ULONG iterations = reload;
    
    /* Loop forever */
    while(1)
    {   
        /* Get Mutex */
        tx_mutex_get(&mutex_0, TX_WAIT_FOREVER);

        /* Takes the time at the start of the job */
        previous = tx_time_get();
        
        /* Each cycle takes about 58 clocks */
        while(iterations)
        {
            /* Turn on Led 1 */
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_4, GPIO_PIN_4);
            
            /* Turn off Leds 1, 2 and 3  */
            GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_1 | GPIO_PIN_0, 0x0);
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_4, 0x0);
            
            /* Pickup the current system time */
            current = tx_time_get();
            
            /* If only one tick has passed, decrement the iterations, if not, just update the previous value */
            if((previous + 1) == current)
            {
                previous = current;
                iterations--;
            }
            else if(previous != current)
            {
                previous = current;
            }
        }
        
         /* Reload the execution cycles */
        iterations = reload;
        
        /* Put Mutex */
        tx_mutex_put(&mutex_0);
        
        /* Suspend thread 3 */
        tx_thread_suspend(&thread_3);
    }
}

/* Resume thread 1 */

void    timer_expiration_1(ULONG expiration_input)
{
    tx_thread_resume(&thread_1); 
}

/* Resume thread 2 */

void    timer_expiration_2(ULONG expiration_input)
{
    tx_thread_resume(&thread_2); 
}

/* Resume thread 3 */

void    timer_expiration_3(ULONG expiration_input)
{
    tx_thread_resume(&thread_3); 
}