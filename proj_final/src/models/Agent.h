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

#include "../misc/Vector.h"
#include "../misc/utils.h"
#include "consts.h"

#ifndef _MODELS_AGENT_H_
#define _MODELS_AGENT_H_
namespace models {
/**
 *   @brief Agent base class
 *
 */
class Agent {
public:
    Agent();

    // Current position, top-left of current tile
    misc::Vector<float> pos;
    // Current velocity
    float vel;
    // Current direction
    misc::Vector<float> direction;

    /**
     *   @brief Update position of agent
     *
     */
    void update_position(float vel_factor);

    /**
    *   @brief Get the agent current tile in labirynth 
    *   
    *   @return misc::Vector<int> agent current tile
    */
    misc::Vector<int> get_agent_tile();
};
} // namespace models
#endif
