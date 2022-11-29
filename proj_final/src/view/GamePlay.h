#include "../models/GamePlay.h"
#include "Base.h"
#include "Ghost.h"
#include "Labirynth.h"
#include "PacMan.h"

#ifndef _VIEW_GAMEPLAY_H_
#define _VIEW_GAMEPLAY_H_

namespace view {
class ViewGamePlay : public Base {
public:
    ViewGamePlay(models::GamePlay* gameplay);

    void draw(sf::RenderWindow* window);
    models::GamePlay* gameplay;

    ViewPacMan view_pac;
    ViewGhost view_ghosts[4];
    ViewLabyrinth view_labyrinth;
};
}
#endif