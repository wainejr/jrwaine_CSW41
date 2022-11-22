#include "./Agent.h"

models::Agent::Agent()
{
    this->pos = misc::Vector<float>(0, 0);
    this->direction = misc::Vector<float>(models::consts::STOP);
    this->vel = 0;
}

void models::Agent::update_position()
{
    misc::Vector<float> sum_val = this->direction.mul(this->vel);
    this->pos.add(sum_val);
}
