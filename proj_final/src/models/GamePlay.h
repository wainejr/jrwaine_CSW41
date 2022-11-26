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
        GAME_FINISHED,
    };
} // namespace UpdateStatus

enum GameState {
    GAME_STATE_RUNNING,
    GAME_STATE_ENDED,
};

class GamePlay {
    misc::t_time last_update_sec;
    misc::t_time start_time;
    bool is_init;

    bool has_collision(PacMan* pac, Ghost* ghost);
    void update_positions(float vel_factor);
    void update_pacman_state();
    void update_ghost_state(Ghost* ghost);
    bool validate_direction_change(Agent* a, misc::Vector<float> direction, bool tunnel_allowed);
    void correct_agent_position(Agent* a, bool tunnel_allowed);
    void update_labyrinth_score();
    void update_agent_direction(Agent* agent, misc::Vector<float> new_direction, bool tunnel_allowed);

    UpdateStatus::myEnum update_gameplay_status();

public:
    PacMan pac;
    Ghost ghosts[4];
    Labyrinth lab;
    Score score;
    GameState gamestate;

    GamePlay();

    UpdateStatus::myEnum update();
    void update_ghost_direction(Ghost* ghost, misc::Vector<float> new_direction);
    void update_pacman_direction(misc::Vector<float> new_direction);
};
} // namespace models
#endif
