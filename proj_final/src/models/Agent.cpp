#include "./Agent.h"

using namespace models;

Agent::Agent()
{
    this->pos = misc::Vector<float>(0, 0);
    this->direction = misc::Vector<float>(consts::STOP);
    this->vel = 0;
}

void Agent::update_position(float vel_factor)
{
    misc::Vector<float> sum_val = this->direction.mul(this->vel * vel_factor);
    this->pos.add(sum_val);
    this->pos.x = misc::remainder_f(this->pos.x, consts::MAZE_SIZE_X - 1);
    this->pos.y = misc::remainder_f(this->pos.y, consts::MAZE_SIZE_Y - 1);
}

misc::Vector<int> get_pos_tile(misc::Vector<float> pos)
{
    return misc::Vector<int>(pos.x, pos.y);
}

misc::Vector<int> Agent::get_agent_tile()
{
    misc::Vector<float> pos_center = misc::Vector<float>(this->pos.x + 0.5f, this->pos.y + 0.5f);
    return get_pos_tile(pos_center);
}