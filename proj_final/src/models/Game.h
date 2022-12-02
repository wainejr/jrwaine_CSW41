/**
 *   @file Game.h
 *   @author Waine Jr. (waine@alunos.utfpr.edu.br)
 *   @brief Rules and management for PacMan global state, such as "menu",
 * "points" or "playing"
 *   @version 0.1.0
 *   @date 21/11/2022
 *
 *   @copyright Copyright (c) 2022
 *
 */

#include "GamePlay.h"

#ifndef _MODELS_GAME_H_
#define _MODELS_GAME_H_
namespace models {

/**
*   @brief Global states for game
*   
*/
enum GlobalStates {
    MENU,
    PLAYING,
    SHOWING_SCORE,
};

/**
*   @brief Game representation, with states and entities required for it
*   
*/
class Game {

public:
    // Current game state
    GlobalStates curr_state;
    // Gameplay representation
    GamePlay gameplay;
    Game();

    /**
    *   @brief State into playing
    *   
    */
    void into_playing();
    
    /**
    *   @brief State into showing score
    *   
    */
    void into_showing_score();

    /**
    *   @brief State into menu
    *   
    */void into_menu();
};
}
#endif
