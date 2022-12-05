#include "../models/Agent.h"
#include "Base.h"

#ifndef _VIEW_AGENT_H_
#define _VIEW_AGENT_H_

namespace view {

/**
*   @brief View for Agent
*   
*/
class ViewAgent {
public:
    ViewAgent(models::Agent* agent);

    models::Agent* agent;

    /**
    *   @brief Draw agent in context with given color
    *   
    *   @param context context to draw
    *   @param color color to use
    */
    void draw_agent(DrawContext* context, unsigned long color);
};
}
#endif