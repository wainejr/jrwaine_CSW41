#include "../models/Game.h"
#include "Base.h"
#include "GamePlay.h"
#include <iostream>
#include <string>

#ifndef _VIEW_GAME_H_
#define _VIEW_GAME_H_

namespace view {

/**
*   @brief View of model Game
*   
*/
class ViewGame : public Base {
    /**
    *   @brief Draw score
    *   
    *   @param context context to draw to
    */
    void draw_score(DrawContext* context);

    /**
    *   @brief Draw menu
    *   
    *   @param context context to draw to
    */
    void draw_menu(DrawContext* context);

public:
    ViewGame(models::Game* game);
    models::Game* game;
    ViewGamePlay view_gameplay;

    /**
    *   @brief Clean screen with black background
    *   
    *   @param context context to draw to
    */
    void clean_screen(DrawContext* context);

    /**
    *   @brief Draw current game view
    *   
    *   @param context 
    */
    void draw(DrawContext* context);
};
}
#endif