#include "../models/PacMan.h"
#include "Base.h"
#include "Agent.h"

#ifndef _VIEW_PACMAN_H_
#define _VIEW_PACMAN_H_

namespace view {
class ViewPacMan : public Base, ViewAgent {
public:
    ViewPacMan(models::PacMan* pac);

    models::PacMan* pac;
    void draw(DrawContext* window);
};
}
#endif