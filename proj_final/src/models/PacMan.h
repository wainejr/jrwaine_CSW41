/**
 *   @file PacMan.h
 *   @author Waine Jr. (waine@alunos.utfpr.edu.br)
 *   @brief PacMan model representation
 *   @version 0.1.0
 *   @date 21/11/2022
 *
 *   @copyright Copyright (c) 2022
 *
 */

#include "Agent.h"

#ifndef _MODELS_PACMAN_H_
#define _MODELS_PACMAN_H_
namespace models {

/**
*   @brief State of PacMan
*       NORMAL: Normal state of pacman
*       SUPER: PacMan is capable of eating ghosts
*
*/
namespace PacmanState {
    enum myEnum { NORMAL,
        SUPER,
        DEAD,
    };
}

/**
 *   @brief Game representation of ghost
 *
 */
class PacMan : public Agent {
    int n_updates_super;

public:
    // Current state of pacman
    PacmanState::myEnum state;
    PacMan();

    /**
    *   @brief Tick update in current pacman state
    *   
    */
    void tick_update();

    /**
    *   @brief Pacman into SUPER state
    *   
    */
    void into_super();
};
} // namespace models
#endif
