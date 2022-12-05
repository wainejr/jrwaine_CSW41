#include "../models/GamePlay.h"
#include "Base.h"
#include "Ghost.h"
#include "Labirynth.h"
#include "PacMan.h"

#ifndef _VIEW_GAMEPLAY_H_
#define _VIEW_GAMEPLAY_H_

namespace view {
/**
*   @brief View for models gameplay class
*   
*/
class ViewGamePlay : public Base {
public:
    ViewGamePlay(models::GamePlay* gameplay);

    /**
    *   @brief Draw gameplay current state
    *   
    *   @param context context to draw to
    */
    void draw(DrawContext* context);
    models::GamePlay* gameplay;

    ViewPacMan view_pac;
    ViewGhost view_ghosts[4];
    ViewLabyrinth view_labyrinth;
};
}
#endif