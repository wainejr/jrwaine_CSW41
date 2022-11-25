#include "update_state.h"

#include "display.h"
#include "control_ghost.h"

#if USE_SFML

void update_state_loop(models::GamePlay* gameplay)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    std::thread thread_ghost0(control_ghost_loop, gameplay, &gameplay->ghosts[0]);
    std::thread thread_ghost1(control_ghost_loop, gameplay, &gameplay->ghosts[1]);
    std::thread thread_ghost2(control_ghost_loop, gameplay, &gameplay->ghosts[2]);
    std::thread thread_ghost3(control_ghost_loop, gameplay, &gameplay->ghosts[3]);

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
}
#else
void update_state_loop(ULONG id)
{
}

#endif