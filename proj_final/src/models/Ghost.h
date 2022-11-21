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

#include "src/models/Agent.h"

using namespace models;

namespace models {
/**
 *   @brief Colors of ghosts
 */
enum GhostColors { RED,
    YELLOW,
    PINK,
    BLUE };

/**
 *   @brief State of ghosts
 *       OUT_CAVE: ghost is coming out of cave
 *       WALKING: ghost currently walking through labyrinth
 *       AFRAID: ghost was eaten by PacMan and is going back to cave
 *
 */
enum GhostState { OUT_CAVE,
    WALKING,
    AFRAID };

/**
 *   @brief Game representation of ghost
 *
 */
class Ghost : public Agent {
public:
    // Color of ghost
    GhostColors color;
    // Current state of ghost
    GhostState state;
};
} // namespace models
