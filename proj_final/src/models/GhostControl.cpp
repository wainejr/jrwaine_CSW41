#include "GhostControl.h"

using namespace models;

GhostControl::GhostControl(GhostControlType control_type, GamePlay* gameplay, Ghost* ghost)
{
    this->gameplay = gameplay;
    this->ghost = ghost;
    this->control_type = control_type;

    this->last_dir = misc::Vector<int>((int)ghost->direction.x, (int)ghost->direction.y);
    this->last_tile = ghost->get_agent_tile();
    this->curr_tile = this->last_tile;
    this->last_tile_dir_updated = misc::Vector<int>(0, 0);
}

void GhostControl::update_direction(misc::Vector<int> new_direction)
{
    misc::Vector<float> dir_float = misc::Vector<float>(new_direction.x, new_direction.y);
    this->gameplay->update_ghost_direction(this->ghost, dir_float);
    // Set last direction to current one, to store it when ghost stops
    this->last_dir = new_direction;
    this->last_tile_dir_updated = this->ghost->get_agent_tile();
}