#include "../models/PacMan.h"
#include "Base.h"

#ifndef _VIEW_PACMAN_H_
#define _VIEW_PACMAN_H_

namespace view {
class ViewPacMan : public Base {
public:
    ViewPacMan(models::PacMan* pac);

    models::PacMan* pac;
    void draw(sf::RenderWindow* window);
};
}
#endif