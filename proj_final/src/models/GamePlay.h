/**
 *   @file GamePlay.h
 *   @author Waine Jr. (waine@alunos.utfpr.edu.br)
 *   @brief Model for rules and logic for PacMan gameplay
 *   @version 0.1.0
 *   @date 21/11/2022
 *
 *   @copyright Copyright (c) 2022
 *
 */
#pragma once

#include "Ghost.h"
#include "Labyrinth.h"
#include "PacMan.h"
#include "Score.h"

#ifndef _MODELS_GAMEPLAY_H_
#define _MODELS_GAMEPLAY_H_
namespace models {

namespace UpdateStatus {
    enum myEnum {
        PACMAN_DIED,
        GAME_CONTINUE,
    };
} // namespace UpdateStatus

class GamePlay {

    bool check_collision(PacMan* pac, Ghost* ghost);
    void update_positions();
    void update_pacman_state();
    void update_ghosts_states();

public:
    PacMan pac;
    Ghost ghosts[4];
    Labyrinth lab;
    Score score;

    GamePlay();

    UpdateStatus::myEnum update();

    void update_pacman_direction(misc::Vector<float> new_direction);
};
} // namespace models
#endif
