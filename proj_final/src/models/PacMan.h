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

#include "src/models/Agent.h"

using namespace models;

namespace models {
/**
 *   @brief State of PacMan
 *       NORMAL: Normal state of pacman
 *       SUPER: PacMan is capable of eating ghosts
 *
 */
enum PacmanState { NORMAL, SUPER };

/**
 *   @brief Game representation of ghost
 *
 */
class PacMan : public Agent {
public:
  // Current state of pacman
  PacmanState state;
};
} // namespace models
