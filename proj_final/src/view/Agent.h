#include "../models/Agent.h"
#include "Base.h"

#ifndef _VIEW_AGENT_H_
#define _VIEW_AGENT_H_

namespace view {
class ViewAgent {
public:
    ViewAgent(models::Agent* agent);

    models::Agent* agent;
    void draw_agent(DrawContext* window, unsigned long color);
};
}
#endif