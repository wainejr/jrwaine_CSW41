#include "./Ghost.h"

using namespace models;

Ghost::Ghost(GhostColors::myEnum color)
    : Agent()
{
    this->color = color;
    this->n_updates_state = 0;
    // Position depending on color
    switch (color) {
    case GhostColors::RED:
        this->state = GhostState::WALKING;
        this->pos = misc::Vector<float>(consts::INITIAL_GHOST_RED_POSITION);
        this->direction = misc::Vector<float>(consts::INITIAL_GHOST_RED_DIRECTION);
        break;
    case GhostColors::BLUE:
        this->state = GhostState::LOCKED_CAVE;
        this->pos = misc::Vector<float>(consts::INITIAL_GHOST_BLUE_POSITION);
        this->direction = misc::Vector<float>(consts::INITIAL_GHOST_BLUE_DIRECTION);
        break;
    case GhostColors::YELLOW:
        this->state = GhostState::LOCKED_CAVE;
        this->pos = misc::Vector<float>(consts::INITIAL_GHOST_YELLOW_POSITION);
        this->direction = misc::Vector<float>(consts::INITIAL_GHOST_YELLOW_DIRECTION);
        break;
    case GhostColors::PINK:
        this->state = GhostState::LOCKED_CAVE;
        this->pos = misc::Vector<float>(consts::INITIAL_GHOST_PINK_POSITION);
        this->direction = misc::Vector<float>(consts::INITIAL_GHOST_PINK_DIRECTION);
        break;
    default:
        this->state = GhostState::LOCKED_CAVE;
        this->pos = misc::Vector<float>(consts::INITIAL_GHOST_PINK_POSITION);
        this->direction = misc::Vector<float>(consts::INITIAL_GHOST_PINK_DIRECTION);
        break;
    }
    this->vel = consts::GHOSTS_VELOCITY_PER_SEC;
}

Ghost::Ghost()
    : Agent()
{
    this->n_updates_state = 0;
    this->color = GhostColors::PINK;
    this->pos = misc::Vector<float>(consts::INITIAL_GHOST_PINK_POSITION);
    this->direction = misc::Vector<float>(consts::INITIAL_GHOST_PINK_DIRECTION);
    this->vel = 0;
    // Ghosts initializes in cave
    this->state = GhostState::OUT_CAVE;
}

void Ghost::tick_update()
{
    this->n_updates_state += 1;
}

void Ghost::into_afraid(){
    this->n_updates_state = 0;
    this->state = GhostState::AFRAID;
}

void Ghost::into_walking(){
    this->n_updates_state = 0;
    this->state = GhostState::WALKING;
}

void Ghost::into_incave()
{
    this->n_updates_state = 0;
    this->state = GhostState::IN_CAVE;
    this->vel = consts::GHOSTS_VELOCITY_PER_SEC * 2;
}

void Ghost::into_outcave()
{
    this->n_updates_state = 0;
    this->state = GhostState::OUT_CAVE;
    this->vel = consts::GHOSTS_VELOCITY_PER_SEC;
}

bool Ghost::is_free_from_cave_lock()
{
    switch (this->color) {
    case GhostColors::YELLOW:
        return this->n_updates_state >= consts::GHOST_YELLOW_FREE_CAVE_N_UPDATES;
    case GhostColors::PINK:
        return this->n_updates_state >= consts::GHOST_PINK_FREE_CAVE_N_UPDATES;
    case GhostColors::BLUE:
        return this->n_updates_state >= consts::GHOST_BLUE_FREE_CAVE_N_UPDATES;
    default:
        return false;
    }
}
