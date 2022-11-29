#include "update_state.h"

#include "control_ghost.h"
#include "display.h"

void menu_loop(models::Game* game)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(
        (int)(1000 * models::consts::STATE_UPDATE_SEC_INTERVAL)));
}

void showing_score_loop(models::Game* game)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(5000));
    game->into_menu();
}

void playing_loop(models::Game* game)
{
    models::GamePlay* gameplay = &game->gameplay;

    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    int start_seed = (int)time(NULL);

    std::thread thread_ghost0(control_ghost_loop, gameplay, &gameplay->ghosts[0], start_seed + 1);
    std::thread thread_ghost1(control_ghost_loop, gameplay, &gameplay->ghosts[1], start_seed + 2);
    std::thread thread_ghost2(control_ghost_loop, gameplay, &gameplay->ghosts[2], start_seed + 3);
    std::thread thread_ghost3(control_ghost_loop, gameplay, &gameplay->ghosts[3], start_seed + 4);

    while (gameplay->gamestate != models::GAME_STATE_ENDED) {
        models::UpdateStatus::myEnum res = gameplay->update();
        if (res == models::UpdateStatus::PACMAN_DIED) {
            break;
        } else if (res == models::UpdateStatus::GAME_FINISHED) {
            break;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(
            (int)(1000 * models::consts::STATE_UPDATE_SEC_INTERVAL)));
    }
    thread_ghost0.join();
    thread_ghost1.join();
    thread_ghost2.join();
    thread_ghost3.join();
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
}

#endif