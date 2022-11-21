/**
 *   @file Agent.h
 *   @author Waine Jr. (waine@alunos.utfpr.edu.br)
 *   @brief Model for agent representation (ghosts and PacMan)
 *   @version 0.1.0
 *   @date 21/11/2022
 *
 *   @copyright Copyright (c) 2022
 *
 */

#include "src/misc/Vector.h"

namespace models {
/**
 *   @brief Agent base class
 *
 */
class Agent {
  // Current position
  misc::Vector<float> pos;
  // Current velocity
  float vel;
  // Current direction
  misc::Vector<float> direction;

  /**
   *   @brief Update position of agent
   *
   */
  void update_position();
};
} // namespace models
