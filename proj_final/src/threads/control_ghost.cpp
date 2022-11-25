#include "control_ghost.h"

void control_incave(models::GhostControl* ghost_control) {

}

void control_outcave(models::GhostControl* ghost_control){

}

void control_walking(models::GhostControl* ghost_control){

}

void control_afraid(models::GhostControl* ghost_control){

}

void control_ghost_loop(models::GamePlay* gameplay, models::Ghost* ghost)
{
    models::GhostControl ghost_control(models::CONTROL_RANDOM, gameplay, ghost);

    while (gameplay->gamestate == models::GAME_STATE_RUNNING) {
        switch (ghost->state) {
        case models::GhostState::IN_CAVE:
            control_incave(&ghost_control);
            break;
        case models::GhostState::OUT_CAVE:
            control_outcave(&ghost_control);
            break;
        case models::GhostState::WALKING:
            control_walking(&ghost_control);
            break;
        case models::GhostState::AFRAID:
            control_afraid(&ghost_control);
            break;
        default:
            break;
        }
    }
}