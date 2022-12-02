#include "display.h"

void display_loop(ULONG id)
{
    models::GlobalStates last_state = g_game.curr_state;
    while (true) {
        if (g_game.curr_state != last_state) {
            g_view_game.clean_screen(&g_context);
            last_state = g_game.curr_state;
        }
        g_view_game.draw(&g_context);
        tx_thread_suspend(&g_thread_display);
    }
}

void timer_display_expiration(ULONG expiration_input)
{
    tx_thread_resume(&g_thread_display);
}

void initialize_thread_display()
{
    /* Memory pointer */
    CHAR* pointer = (CHAR*)TX_NULL;

    /* Allocate the stack for display thread  */
    tx_byte_allocate(&g_byte_pool, (VOID**)&pointer, STACK_SIZE, TX_NO_WAIT);

    /* Create the thread for display  */
    tx_thread_create(&g_thread_display, "thread display", display_loop, 0, pointer,
        STACK_SIZE, 0, 0, 0, TX_AUTO_START);

    /* Create the timer for display */
    tx_timer_create(&g_timer_display, "timer display", timer_display_expiration, 1,
        THREAD_DISPLAY_PERIOD, THREAD_DISPLAY_PERIOD, TX_AUTO_ACTIVATE);
}
