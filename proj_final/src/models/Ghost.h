/**
 *   @file Ghost.h
 *   @author Waine Jr. (waine@alunos.utfpr.edu.br)
 *   @brief Model for ghost representation
 *   @version 0.1.0
 *   @date 21/11/2022
 *
 *   @copyright Copyright (c) 2022
 *
 */

#include "Agent.h"

#ifndef _MODELS_GHOSTS_H_
#define _MODELS_GHOSTS_H_
namespace models {

    /**
     *   @brief Colors of ghosts
     */
namespace GhostColors {
    enum myEnum { RED,
        ORANGE,
        PINK,
        BLUE };
}

    /**
     *   @brief State of ghosts
     *       OUT_CAVE: ghost is coming out of cave
     *       WALKING: ghost currently walking through labyrinth
     *       AFRAID: ghost was eaten by PacMan and is going back to cave
     *
     */
namespace GhostState {
    enum myEnum { OUT_CAVE,
        WALKING,
        AFRAID,
        EATEN,
        LOCKED_CAVE,
    };
}

/**
 *   @brief Game representation of ghost
 *
 */
class Ghost : public Agent {

public:
    // Color of ghost
    GhostColors::myEnum color;
    // Current state of ghost
    GhostState::myEnum state;

    Ghost();
    Ghost(GhostColors::myEnum color);

    // Number of updates in current state
    int n_updates_state;

    /**
    *   @brief Tick update for ghost current state
    *   
    */
    void tick_update();

    /**
    *   @brief Ghost into AFRAID state
    *   
    */
    void into_afraid();
    
    /**
    *   @brief Ghost into WALKING state
    *   
    */
    void into_walking();
    
    /**
    *   @brief Ghost into EATEN state
    *   
    */
    void into_eaten();
    
    /**
    *   @brief Ghost into OUT_CAVE state
    *   
    */
    void into_outcave();
    
    /**
    *   @brief Is ghost free from cave lock
    *   
    *   @return true ghost is free
    *   @return false ghost is not free
    */
    bool is_free_from_cave_lock();
};
} // namespace models
#endif