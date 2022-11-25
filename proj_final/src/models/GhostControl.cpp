#include "GhostControl.h"

using namespace models;

GhostControl::GhostControl(GhostControlType control_type, GamePlay* gameplay, Ghost* ghost)
{
    this->gameplay = gameplay;
    this->ghost = ghost;
    this->control_type = control_type;

    this->last_dir = ghost->direction;
    this->last_tile = ghost->get_agent_tile();

    this->curr_path_pos = 0;
    this->path_size = 0;
    for (int i = 0; i < 100; i++) {
        this->path_follow[i] = misc::Vector<int>(0, 0);
    }
}
