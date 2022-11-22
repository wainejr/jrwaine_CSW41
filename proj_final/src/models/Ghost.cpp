#include "./Ghost.h"

models::Ghost::Ghost(GhostColors::myEnum color)
    : Agent()
{
    this->color = color;
    // Position depending on color
    switch (color) {
    case GhostColors::RED:
        this->pos = misc::Vector<float>(consts::INITIAL_GHOST_RED_POSITION);
        this->direction = misc::Vector<float>(consts::INITIAL_GHOST_RED_DIRECTION);
        break;
    case GhostColors::BLUE:
        this->pos = misc::Vector<float>(consts::INITIAL_GHOST_BLUE_POSITION);
        this->direction = misc::Vector<float>(consts::INITIAL_GHOST_BLUE_DIRECTION);
        break;
    case GhostColors::YELLOW:
        this->pos = misc::Vector<float>(consts::INITIAL_GHOST_YELLOW_POSITION);
        this->direction = misc::Vector<float>(consts::INITIAL_GHOST_YELLOW_DIRECTION);
        break;
    case GhostColors::PINK:
        this->pos = misc::Vector<float>(consts::INITIAL_GHOST_PINK_POSITION);
        this->direction = misc::Vector<float>(consts::INITIAL_GHOST_PINK_DIRECTION);
        break;
    default:
        break;
    }
    this->vel = consts::GHOSTS_VELOCITY;
    // Ghosts initializes in cave
    this->state = GhostState::OUT_CAVE;
}

models::Ghost::Ghost()
    : Agent()
{

    this->color = GhostColors::PINK;
    this->pos = misc::Vector<float>(consts::INITIAL_GHOST_PINK_POSITION);
    this->direction = misc::Vector<float>(consts::INITIAL_GHOST_PINK_DIRECTION);
    this->vel = 0;
    // Ghosts initializes in cave
    this->state = GhostState::OUT_CAVE;
}