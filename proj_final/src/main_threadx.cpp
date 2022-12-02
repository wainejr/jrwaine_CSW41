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
#include "stdbool.h"
#include "stdint.h"

#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include "grlib/grlib.h"
#include "inc/hw_memmap.h"
#include "stdio.h"
#include "tx_api.h"
#include "drivers/all.h"
#include "threads/actions.h"
#include "threads/control_ghost.h"
#include "threads/display.h"
#include "threads/update_state.h"
#include "view/Game.h"

/*------------------------------------------------------------------------------
 *
 *      Gloval vars declarations
 *
 *------------------------------------------------------------------------------*/

#define THREAD_PERIOD(period_sec) (int)((period_sec)*TX_TIMER_TICKS_PER_SECOND)
#define THREAD_DISPLAY_PERIOD THREAD_PERIOD(1.0f / view::globals::DESIRED_FPS)
#define THREAD_AUDIO_PERIOD (THREAD_DISPLAY_PERIOD * 5)

/* Define the ThreadX object control blocks...  */

TX_THREAD thread_input;
TX_THREAD g_thread_display;
TX_THREAD g_thread_state;
TX_THREAD g_thread_actions;
TX_THREAD g_thread_ghosts[4];

TX_TIMER g_timer_display;
TX_TIMER g_timer_state;
TX_TIMER g_timer_actions;

TX_BYTE_POOL g_byte_pool;

TX_BYTE_POOL byte_pool_0;
TX_MUTEX mutex_0;
TX_TIMER timer_display;
TX_TIMER timer_state;
TX_TIMER timer_input;
TX_TIMER timer_ghosts[4];

/* Define byte pool memory.  */

UCHAR byte_pool_memory[BYTE_POOL_SIZE];

models::Game g_game;
tContext g_context;
view::ViewGame g_view_game(&g_game);

/*------------------------------------------------------------------------------
 *
 *      Functions and Methods
 *
 *------------------------------------------------------------------------------*/

/* Define thread prototypes.  */

void thread_display_entry(ULONG thread_id);
void thread_state_entry(ULONG thread_id);
void thread_input_entry(ULONG thread_id);
void thread_audio_entry(ULONG thread_id);
void thread_ghost_entry(ULONG thread_id);

void thread_1_entry(ULONG reload);
void thread_1_m_entry(ULONG reload);

/* Define timer prototype.  */
void timer_display_expiration(ULONG expiration_input);
void timer_state_expiration(ULONG expiration_input);
void timer_input_expiration(ULONG expiration_input);
void timer_audio_expiration(ULONG expiration_input);

/* Define main entry point.  */
int main()
{
    /* Sets the system clock to 120 MHz. */
    uint32_t ui32SysClock = SysCtlClockFreqSet((SYSCTL_XTAL_25MHZ | SYSCTL_OSC_MAIN | SYSCTL_USE_PLL | SYSCTL_CFG_VCO_240), 120000000);
    drivers::setup_all(&g_context);

    g_view_game.clean_screen(&g_context);

    // test_game_draw();

    /* Enter the ThreadX kernel.  */
    tx_kernel_enter();
}

/* Define what the initial system looks like.  */
void tx_application_define(void* first_unused_memory)
{
    /* Memory pointer */
    CHAR* pointer = (CHAR*)TX_NULL;

    /* Create a byte memory pool from which to allocate the thread stacks.  */
    tx_byte_pool_create(&g_byte_pool, "global byte pool", byte_pool_memory, BYTE_POOL_SIZE);

    initialize_thread_update_state();
    initialize_thread_display();
    initialize_thread_actions();
    initialize_threads_control_ghosts();

    /* Set internal system clock to zero */
    tx_time_set(0x0);
}
