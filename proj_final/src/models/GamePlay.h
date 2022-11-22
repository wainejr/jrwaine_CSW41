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
class GamePlay {
    PacMan pac;
    Ghost ghosts[4];
    Labyrinth lab;
    Score score;

public:
    GamePlay();
};
} // namespace models
#endif
