#include "update_state.h"

#include "control_ghost.h"
#include "display.h"

void menu_loop(models::Game* game)
{
    // Sleep for 250ms
    tx_thread_sleep((250 * TX_TIMER_TICKS_PER_SECOND) / 1000);
}

void showing_score_loop(models::Game* game)
{
    // Sleep for 5 seconds, to show score for 5 seconds
    tx_thread_sleep(5 * TX_TIMER_TICKS_PER_SECOND);
    game->into_menu();
}

void playing_loop(models::Game* game)
{
    models::GamePlay* gameplay = &game->gameplay;

    // Resume ghost threads
    tx_thread_resume(&g_thread_ghosts[0]);
    tx_thread_resume(&g_thread_ghosts[1]);
    tx_thread_resume(&g_thread_ghosts[2]);
    tx_thread_resume(&g_thread_ghosts[3]);
    // Sleep for 1000ms
    tx_thread_sleep((1000 * TX_TIMER_TICKS_PER_SECOND) / 1000);

    while (gameplay->gamestate != models::GAMEPLAY_STATE_ENDED) {
        models::UpdateStatus::myEnum res = gameplay->update();
        if (res == models::UpdateStatus::PACMAN_DIED) {
            break;
        } else if (res == models::UpdateStatus::GAME_FINISHED) {
            break;
        }

        tx_thread_sleep(THREAD_UPDATE_STATE_PERIOD);
    }

    game->into_showing_score();
}


void update_state_loop(ULONG id)
{
    while (true) {
        switch (g_game.curr_state) {
        case models::GlobalStates::PLAYING:
            playing_loop(&g_game);
            break;
        case models::GlobalStates::MENU:
            menu_loop(&g_game);
            break;
        case models::GlobalStates::SHOWING_SCORE:
            showing_score_loop(&g_game);
            break;
        default:
            break;
        }
    }
}

void initialize_thread_update_state()
{
    /* Memory pointer */
    CHAR* pointer = (CHAR*)TX_NULL;

    /* Allocate the stack for thread 1.  */
    tx_byte_allocate(&g_byte_pool, (VOID**)&pointer, STACK_SIZE, TX_NO_WAIT);

    /* Create the thread for state  */
    tx_thread_create(&g_thread_state, "thread state", update_state_loop, 0, pointer,
        STACK_SIZE, 0, 0, TX_NO_TIME_SLICE, TX_AUTO_START);
}
