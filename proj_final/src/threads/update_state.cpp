#include "update_state.h"

#include "control_ghost.h"
#include "display.h"

void menu_loop(models::Game* game)
{   
    #if USE_SFML
    std::this_thread::sleep_for(std::chrono::milliseconds(
        (int)(1000 * models::consts::STATE_UPDATE_SEC_INTERVAL)));
    #else
    // Sleep for 250ms
    tx_thread_sleep((250*TX_TIMER_TICKS_PER_SECOND)/1000);
    #endif
}

void showing_score_loop(models::Game* game)
{
    #if USE_SFML
    std::this_thread::sleep_for(std::chrono::milliseconds(5000));
    #else
    // Sleep for 5 seconds, to show score for 5 seconds
    tx_thread_sleep(5*TX_TIMER_TICKS_PER_SECOND);
    #endif 
    game->into_menu();
}

void playing_loop(models::Game* game)
{
    models::GamePlay* gameplay = &game->gameplay;

    #if USE_SFML
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    int start_seed = (int)time(NULL);
    std::thread thread_ghost0(control_ghost_loop, gameplay, &gameplay->ghosts[0], start_seed + 1);
    std::thread thread_ghost1(control_ghost_loop, gameplay, &gameplay->ghosts[1], start_seed + 2);
    std::thread thread_ghost2(control_ghost_loop, gameplay, &gameplay->ghosts[2], start_seed + 3);
    std::thread thread_ghost3(control_ghost_loop, gameplay, &gameplay->ghosts[3], start_seed + 4);
    #else

    // Resume ghost threads
    tx_thread_resume(&g_thread_ghosts[0]);
    tx_thread_resume(&g_thread_ghosts[1]);
    tx_thread_resume(&g_thread_ghosts[2]);
    tx_thread_resume(&g_thread_ghosts[3]);
    // Sleep for 1000ms
    tx_thread_sleep((1000*TX_TIMER_TICKS_PER_SECOND)/1000);

    #endif

    while (gameplay->gamestate != models::GAME_STATE_ENDED) {
        models::UpdateStatus::myEnum res = gameplay->update();
        if (res == models::UpdateStatus::PACMAN_DIED) {
            break;
        } else if (res == models::UpdateStatus::GAME_FINISHED) {
            break;
        }
        #if USE_SFML
        std::this_thread::sleep_for(std::chrono::milliseconds(
            (int)(1000 * models::consts::STATE_UPDATE_SEC_INTERVAL)));
        #else
        tx_thread_sleep(THREAD_UPDATE_STATE_PERIOD);
        #endif

    }
    #if USE_SFML
    thread_ghost0.join();
    thread_ghost1.join();
    thread_ghost2.join();
    thread_ghost3.join();
    #endif

    game->into_showing_score();
}

#if USE_SFML

void update_state_loop(models::Game* game)
{
    while (true) {
        switch (game->curr_state) {
        case models::GlobalStates::PLAYING:
            playing_loop(game);
            break;
        case models::GlobalStates::MENU:
            menu_loop(game);
            break;
        case models::GlobalStates::SHOWING_SCORE:
            showing_score_loop(game);
            break;
        default:
            break;
        }
    }
}
#else
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

void initialize_thread_update_state(){
    /* Memory pointer */
    CHAR *pointer = (CHAR*)TX_NULL;

    /* Allocate the stack for thread 1.  */
    tx_byte_allocate(&g_byte_pool, (VOID **) &pointer, STACK_SIZE, TX_NO_WAIT);

    /* Create the thread for state  */
    tx_thread_create(&g_thread_state, "thread state", update_state_loop, 0, pointer, 
        STACK_SIZE, 0, 0, 5, TX_AUTO_START);
}

#endif