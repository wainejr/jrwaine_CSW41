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

namespace models{

    enum GlobalStates{
        MENU,
        PLAYING,
        SHOWING_SCORE,
    };

    class Game
    {

    public:
        GlobalStates curr_state;
        GamePlay gameplay;
        Game();

        GlobalStates state_machine();

        void loop_playing();
        void loop_menu();
        void loop_showing_score();

        void into_playing();
        void into_showing_score();
        void into_menu();
    };
    
    
}
