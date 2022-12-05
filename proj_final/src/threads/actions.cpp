#include "actions.h"

void state_machine_playing()
{
    misc::Vector<int> joystick = drivers::get_joystick_pos();

    if (joystick.x == 0 && joystick.y == 0) {
        return;
    } else if (joystick.x == 1 && joystick.y == 0) {
        g_game.gameplay.update_pacman_direction(models::consts::RIGHT);
    } else if (joystick.x == -1 && joystick.y == 0) {
        g_game.gameplay.update_pacman_direction(models::consts::LEFT);
    } else if (joystick.x == 0 && joystick.y == 1) {
        g_game.gameplay.update_pacman_direction(models::consts::UP);
    } else if (joystick.x == 0 && joystick.y == -1) {
        g_game.gameplay.update_pacman_direction(models::consts::DOWN);
    }
}

void state_machine_menu()
{
    if (drivers::get_button_pressed()) {
        g_game.into_playing();
    }
}

void actions_loop(ULONG id)
{
    while (true) {
        switch (g_game.curr_state) {
        case models::GlobalStates::PLAYING:
            state_machine_playing();
            break;
        case models::GlobalStates::MENU:
            state_machine_menu();
            break;
        default:
            break;
        }
        tx_thread_suspend(&g_thread_actions);
    }
}

void timer_actions_expiration(ULONG expiration_input)
{
    tx_thread_resume(&g_thread_actions);
}

void initialize_thread_actions()
{
    /* Memory pointer */
    CHAR* pointer = (CHAR*)TX_NULL;

    /* Allocate the stack for display thread  */
    tx_byte_allocate(&g_byte_pool, (VOID**)&pointer, STACK_SIZE, TX_NO_WAIT);

    /* Create the thread for display  */
    tx_thread_create(&g_thread_actions, "thread actions", actions_loop, 0, pointer,
        STACK_SIZE, 0, 0, TX_NO_TIME_SLICE, TX_AUTO_START);

    /* Create the timer for display */
    tx_timer_create(&g_timer_actions, "timer actions", timer_actions_expiration, 1,
        THREAD_ACTIONS_PERIOD, THREAD_ACTIONS_PERIOD, TX_AUTO_ACTIVATE);
}
