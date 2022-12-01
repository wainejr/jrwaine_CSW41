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
#include "stdio.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include "grlib/grlib.h"
#include "inc/hw_memmap.h"

#include "drivers/all.h"
#include "view/Game.h"

/*------------------------------------------------------------------------------
 *
 *      Gloval vars declarations
 *
 *------------------------------------------------------------------------------*/

#define STACK_SIZE         2048
#define BYTE_POOL_SIZE     (STACK_SIZE*8)

#define THREAD_PERIOD(period_sec)   (int)((period_sec)*TX_TIMER_TICKS_PER_SECOND)
#define THREAD_DISPLAY_PERIOD       THREAD_PERIOD(1.0f/view::globals::DESIRED_FPS)
#define THREAD_STATE_PERIOD         THREAD_PERIOD(1.0f/models::consts::STATE_UPDATE_SEC_INTERVAL)
#define THREAD_AUDIO_PERIOD         (THREAD_DISPLAY_PERIOD*5)
#define THREAD_GHOST_PERIOD         (THREAD_STATE_PERIOD*5)

/* Define the ThreadX object control blocks...  */

TX_THREAD               thread_display;
TX_THREAD               thread_state;
TX_THREAD               thread_input;
TX_THREAD               thread_ghosts[4];

TX_BYTE_POOL            byte_pool_0;
TX_MUTEX                mutex_0;
TX_TIMER                timer_display;
TX_TIMER                timer_state;
TX_TIMER                timer_input;
TX_TIMER                timer_ghosts[4];

/* Define byte pool memory.  */

UCHAR                   byte_pool_memory[BYTE_POOL_SIZE];

tContext sContext;
models::Game game;
view::ViewGame view_game(&game);


/*------------------------------------------------------------------------------
 *
 *      Functions and Methods
 *
 *------------------------------------------------------------------------------*/

/* Define thread prototypes.  */

void    thread_display_entry(ULONG thread_id);
void    thread_state_entry(ULONG thread_id);
void    thread_input_entry(ULONG thread_id);
void    thread_audio_entry(ULONG thread_id);
void    thread_ghost_entry(ULONG thread_id);

void    thread_1_entry(ULONG reload);
void    thread_1_m_entry(ULONG reload);

/* Define timer prototype.  */
void    timer_display_expiration(ULONG expiration_input);
void    timer_state_expiration(ULONG expiration_input);
void    timer_input_expiration(ULONG expiration_input);
void    timer_audio_expiration(ULONG expiration_input);


void test_joystick(){
    while(true){
      int val_x = drivers::get_joystick_x();
      int val_y = drivers::get_joystick_y();
      misc::Vector<int> pos = drivers::get_joystick_pos();
      printf("x y %d %d pos (%d %d)\n", val_x, val_y, pos.x, pos.y);
    }
}

void test_button(){
    while(true){
      bool button = drivers::get_button_pressed();
      printf("button %d\n", (int)button);
    }
}

void test_buzzer(){
    while(true){
      bool button = drivers::get_button_pressed();
      if(button){
        drivers::update_buzzer_value(1.0f);
      }else{
        drivers::update_buzzer_value(0.0f);
      }
      SysCtlDelay(10000);
    }
}

void test_display(){
    GrContextForegroundSet(&sContext, ClrWhite);
    GrContextBackgroundSet(&sContext, ClrBlack);

    GrStringDraw(&sContext,"Exempleae", -1, 0, (sContext.psFont->ui8Height+2)*0, true);
    GrStringDraw(&sContext,"Tiva + BoosterPack", -1, 0, (sContext.psFont->ui8Height+2)*1, true);
    GrStringDraw(&sContext,"---------------------", -1, 0, (sContext.psFont->ui8Height+2)*2, true);
    tRectangle rect{
      40, 40, 80, 80
    };

    // GrRectFill(&sContext, &rect, (unsigned long)greenColor);
    GrContextForegroundSet(&sContext, ClrGreen);
    GrRectFill(&sContext, &rect);
    GrRectDraw(&sContext, &rect);
    
    while(true){}
}

void test_menu_draw(){
    game.into_menu();
    view_game.draw(&sContext);
    
    while(true){}
}

void test_game_draw(){
    game.into_playing();
    view_game.draw(&sContext);
    
    while(true){}
}

void test_score_draw(){
    game.into_showing_score();
    game.gameplay.score.curr_score = 128.8f;
    view_game.draw(&sContext);
    
    while(true){}
}


/* Define main entry point.  */
int main()
{
    /* Sets the system clock to 120 MHz. */
    uint32_t ui32SysClock = SysCtlClockFreqSet((SYSCTL_XTAL_25MHZ | SYSCTL_OSC_MAIN | SYSCTL_USE_PLL | SYSCTL_CFG_VCO_240), 120000000);
    drivers::setup_all(&sContext);

    // test_game_draw();

    /* Enter the ThreadX kernel.  */
    tx_kernel_enter();
}


/* Define what the initial system looks like.  */
void    tx_application_define(void *first_unused_memory)
{
    /* Memory pointer */
    CHAR *pointer = (CHAR*)TX_NULL;

    /* Create a byte memory pool from which to allocate the thread stacks.  */
    tx_byte_pool_create(&byte_pool_0, "byte pool 0", byte_pool_memory, BYTE_POOL_SIZE);

    /* Allocate the stack for thread 1.  */
    tx_byte_allocate(&byte_pool_0, (VOID **) &pointer, STACK_SIZE, TX_NO_WAIT);

    /* Create the thread 1.  */
    tx_thread_create(&thread_1, "thread 1", thread_1_m_entry, THREAD_1_INPUT, pointer, STACK_SIZE, 0, 0, TX_NO_TIME_SLICE, TX_AUTO_START);
    
    /* Allocate the stack for thread 2.  */
    tx_byte_allocate(&byte_pool_0, (VOID **) &pointer, STACK_SIZE, TX_NO_WAIT);

    /* Create the thread 2.  */
    tx_thread_create(&thread_2, "thread 2", thread_2_entry, THREAD_2_INPUT, pointer, STACK_SIZE, 15, 15, TX_NO_TIME_SLICE, TX_AUTO_START);
    
    /* Allocate the stack for thread 3.  */
    tx_byte_allocate(&byte_pool_0, (VOID **) &pointer, STACK_SIZE, TX_NO_WAIT);

    /* Create the thread 3.  */
    tx_thread_create(&thread_3, "thread 3", thread_3_m_entry, THREAD_3_INPUT, pointer, STACK_SIZE, 25, 25, TX_NO_TIME_SLICE, TX_AUTO_START);
    
    /* Create the mutex used by thread 1 and 3 with priority inheritance. */
    tx_mutex_create(&mutex_0, "mutex 0", TX_INHERIT);

    /* Create the timer 1. */
    tx_timer_create(
                    &timer_1, "timer 1", timer_expiration_1, 1, 
                    TX_TIMER_TICKS_PER_SECOND * 1, TX_TIMER_TICKS_PER_SECOND * 1, TX_AUTO_ACTIVATE);    
 
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


/* Resume thread 1 */

void    timer_expiration_1(ULONG expiration_input)
{
    tx_thread_resume(&thread_1); 
}
