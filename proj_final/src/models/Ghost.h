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

namespace GhostColors {
    /**
     *   @brief Colors of ghosts
     */
    enum myEnum { RED,
        YELLOW,
        PINK,
        BLUE };
}

namespace GhostState {
    /**
     *   @brief State of ghosts
     *       OUT_CAVE: ghost is coming out of cave
     *       WALKING: ghost currently walking through labyrinth
     *       AFRAID: ghost was eaten by PacMan and is going back to cave
     *
     */
    enum myEnum { OUT_CAVE,
        WALKING,
        AFRAID,
        IN_CAVE,
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

    int n_updates_state;
    void tick_update();

    void into_afraid();
    void into_walking();
    void into_incave();
    void into_outcave();
};
} // namespace models
#endif