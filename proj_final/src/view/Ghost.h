#include "../models/Ghost.h"
#include "Agent.h"
#include "Base.h"

#ifndef _VIEW_GHOST_H_
#define _VIEW_GHOST_H_

namespace view {

/**
*   @brief View for ghost model
*   
*/
class ViewGhost : public Base, ViewAgent {
public:
    ViewGhost(models::Ghost* ghost);

    models::Ghost* ghost;
    /**
    *   @brief Draw current ghost state
    *   
    *   @param context context to draw to
    */
    void draw(DrawContext* context);
};
}
#endif