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

/* Define the ThreadX object control blocks...  */

TX_THREAD g_thread_display;
TX_THREAD g_thread_state;
TX_THREAD g_thread_actions;
TX_THREAD g_thread_ghosts[4];

TX_TIMER g_timer_display;
TX_TIMER g_timer_state;
TX_TIMER g_timer_actions;

TX_BYTE_POOL g_byte_pool;

TX_TIMER timer_display;

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
