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

#include "src/models/Ghost.h"
#include "src/models/Labyrinth.h"
#include "src/models/PacMan.h"

using namespace models;

namespace models {
class GamePlay {

    PacMan pac;
    Ghost ghosts[4];
    Labyrinth lab;

public:
    GamePlay();
};
} // namespace models