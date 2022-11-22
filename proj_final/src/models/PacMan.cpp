#include "./PacMan.h"

models::PacMan::PacMan()
{
    this->pos = misc::Vector<float>(consts::INITIAL_PACMAN_POSITION);
    this->vel = consts::PACMAN_VELOCITY;
    this->direction = misc::Vector<float>(consts::INITIAL_PACMAN_DIRECTION);
    this->state = PacmanState::NORMAL;
}