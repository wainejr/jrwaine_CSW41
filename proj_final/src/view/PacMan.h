#include "../models/PacMan.h"
#include "Agent.h"
#include "Base.h"

#ifndef _VIEW_PACMAN_H_
#define _VIEW_PACMAN_H_

namespace view {
/**
*   @brief View of PacMan model
*   
*/
class ViewPacMan : public Base, ViewAgent {
public:
    ViewPacMan(models::PacMan* pac);

    models::PacMan* pac;
    /**
    *   @brief Draw pacman current state
    *   
    *   @param context context to draw to
    */
    void draw(DrawContext* context);
};
}
#endif