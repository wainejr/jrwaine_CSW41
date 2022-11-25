#include "update_state.h"

#include "display.h"

#if USE_SFML

void update_state_loop(models::GamePlay* gameplay)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    while (true) {
        models::UpdateStatus::myEnum res = gameplay->update();
        if (res == models::UpdateStatus::PACMAN_DIED) {
            break;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(
            (int)(1000 * models::consts::STATE_UPDATE_SEC_INTERVAL)));
    }
}
#else
void update_state_loop(ULONG id)
{
}

#endif