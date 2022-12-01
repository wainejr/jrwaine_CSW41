#include "PacMan.h"

using namespace view;

ViewPacMan::ViewPacMan(models::PacMan* pac)
    : ViewAgent(pac)
    , pac(pac)
{
}

void ViewPacMan::draw(DrawContext* context)
{
    this->draw_agent(context, ClrYellow);
}
