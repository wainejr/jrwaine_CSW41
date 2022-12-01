#include "../models/Ghost.h"
#include "Base.h"
#include "Agent.h"

#ifndef _VIEW_GHOST_H_
#define _VIEW_GHOST_H_

namespace view {
class ViewGhost : public Base, ViewAgent {
public:
    ViewGhost(models::Ghost* ghost);

    models::Ghost* ghost;
    void draw(DrawContext* window);
};
}
#endif