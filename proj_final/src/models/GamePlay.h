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

/**
*   @brief Game update status options
*   
*/
namespace UpdateStatus {
    enum myEnum {
        PACMAN_DIED,
        GAME_CONTINUE,
        GAME_FINISHED,
    };
} // namespace UpdateStatus

/**
*   @brief Current gameplay state
*   
*/
enum GamePlayState {
    GAMEPLAY_STATE_RUNNING,
    GAMEPLAY_STATE_ENDED,
};

/**
*   @brief Gameplay representation (Labyrinth, Pacman, Ghosts, rules, etc.)
*   
*/
class GamePlay {
    // Gameplay is initialized or not
    bool is_init;

    /**
    *   @brief Check collision between pacman and ghost
    *   
    *   @param pac Pacman
    *   @param ghost Ghost
    *   @return true Agents are colliding
    *   @return false Agents are not colliding
    */
    bool has_collision(PacMan* pac, Ghost* ghost);
    
    /**
    *   @brief Update position of agents
    *   
    *   @param vel_factor Factor to multiply velocity (due to interval to update)
    */
    void update_positions(float vel_factor);

    /**
    *   @brief Update current pacman state
    *   
    */
    void update_pacman_state();

    /**
    *   @brief Update current ghost state
    *   
    *   @param ghost Ghost to update
    */
    void update_ghost_state(Ghost* ghost);

    /**
    *   @brief Validate the change of direction of an agent
    *   
    *   @param a agent to check
    *   @param direction direction to set
    *   @param tunnel_allowed is tunnel allowed for agent movement
    *   @return true Direction is currently allowed for agent
    *   @return false Direction is currently not allowed for agent
    */
    bool validate_direction_change(Agent* a, misc::Vector<float> direction, bool tunnel_allowed);
    /**
    *   @brief Correct an agent position in the maze
    *   
    *   @param a Agent to correct position
    *   @param tunnel_allowed is tunnel allowed for agent movement
    *   @param correct_perpendicular correct agent perpendicular position (relative to velocity)
    */
    void correct_agent_position(Agent* a, bool tunnel_allowed, bool correct_perpendicular);
    /**
    *   @brief Update score and labirynth
    *   
    */
    void update_labyrinth_score();
    /**
    *   @brief Update an agent direction
    *   
    *   @param agent agent to update direction
    *   @param new_direction new agent direction
    *   @param tunnel_allowed is tunnel allowed for agent movement
    */
    void update_agent_direction(Agent* agent, misc::Vector<float> new_direction, bool tunnel_allowed);

    /**
    *   @brief Update gameplay state
    *   
    *   @return UpdateStatus::myEnum current gameplay status 
    */
    UpdateStatus::myEnum update_gameplay_status();

public:
    PacMan pac;
    Ghost ghosts[4];
    Labyrinth lab;
    Score score;
    GamePlayState gamestate;

    GamePlay();

    /**
    *   @brief Update gameplay
    *   
    *   @return UpdateStatus::myEnum new gameplay status 
    */
    UpdateStatus::myEnum update();

    /**
    *   @brief Update ghost direction
    *   
    *   @param ghost ghot to update direction
    *   @param new_direction direction to set
    */
    void update_ghost_direction(Ghost* ghost, misc::Vector<float> new_direction);

    /**
    *   @brief Update pacman direction
    *   
    *   @param new_direction direction to set
    */
    void update_pacman_direction(misc::Vector<float> new_direction);
};
} // namespace models
#endif
