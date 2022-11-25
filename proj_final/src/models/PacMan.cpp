#include "./PacMan.h"

using namespace models;

PacMan::PacMan()
{
    this->pos = misc::Vector<float>(consts::INITIAL_PACMAN_POSITION);
    this->vel = consts::PACMAN_VELOCITY_PER_SEC;
    this->direction = misc::Vector<float>(consts::INITIAL_PACMAN_DIRECTION);
    this->state = PacmanState::NORMAL;
    this->n_updates_super = 0;
}

void PacMan::tick_update()
{
    if (this->state == PacmanState::SUPER) {
        this->n_updates_super += 1;
    }
    if (this->n_updates_super >= consts::N_UPDATES_SUPER_PACMAN) {
        this->state = PacmanState::NORMAL;
    }
}

void PacMan::into_super()
{
    this->state = PacmanState::SUPER;
    this->n_updates_super = 0;
}