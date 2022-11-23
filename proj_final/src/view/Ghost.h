#include "../models/Ghost.h"
#include "Base.h"

#ifndef _VIEW_GHOST_H_
#define _VIEW_GHOST_H_

namespace view {
class ViewGhost : public Base {
public:
    ViewGhost(models::Ghost* ghost);

    models::Ghost* ghost;
    void draw(sf::RenderWindow* window);
};
}
#endif