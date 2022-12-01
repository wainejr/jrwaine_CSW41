#include "Ghost.h"

using namespace view;

ViewGhost::ViewGhost(models::Ghost* ghost)
    : ViewAgent(ghost)
    , ghost(ghost)
{
}

void ViewGhost::draw(DrawContext* context)
{
    unsigned long color = 0;

    if (this->ghost->state == models::GhostState::AFRAID) {
        color = ClrBlue;
    } else if (this->ghost->state == models::GhostState::IN_CAVE) {
        color = ClrWhiteSmoke;
    } else {
        switch (this->ghost->color) {
        case models::GhostColors::BLUE:
            color = ClrCyan;
            break;
        case models::GhostColors::RED:
            color = ClrRed;
            break;
        case models::GhostColors::PINK:
            color = ClrPink;
            break;
        case models::GhostColors::ORANGE:
            color = ClrOrange;
            break;
        default:
            break;
        }
    }
    this->draw_agent(context, color);
}
