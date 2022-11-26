#include "Ghost.h"

using namespace view;

ViewGhost::ViewGhost(models::Ghost* ghost)
    : ghost(ghost)
{
}

void ViewGhost::draw(sf::RenderWindow* window)
{
    float abs_pos_x, abs_pos_y;
    const float factor = 0.8f;
    float center_pos_x = this->ghost->pos.x + 0.5;
    float center_pos_y = this->ghost->pos.y + 0.5;
    globals::get_normalized_pos(center_pos_x, center_pos_y, &abs_pos_x, &abs_pos_y);
    abs_pos_x = abs_pos_x - globals::GHOST_RADIUS;
    abs_pos_y = abs_pos_y - globals::GHOST_RADIUS;

#if USE_SFML
    sf::CircleShape ghost(globals::GHOST_RADIUS);
    if (this->ghost->state == models::GhostState::AFRAID) {
        ghost.setFillColor(sf::Color(0, 0, 255));
    } else if (this->ghost->state == models::GhostState::IN_CAVE) {
        ghost.setFillColor(sf::Color(255, 255, 255));
    } else {
        switch (this->ghost->color) {
        case models::GhostColors::BLUE:
            ghost.setFillColor(sf::Color(0, 255, 255));
            break;
        case models::GhostColors::RED:
            ghost.setFillColor(sf::Color(255, 0, 0));
            break;
        case models::GhostColors::PINK:
            ghost.setFillColor(sf::Color(255, 105, 180));
            break;
        case models::GhostColors::ORANGE:
            ghost.setFillColor(sf::Color(255, 109, 10));
            break;
        default:
            break;
        }
    }

    ghost.setPosition(sf::Vector2f(abs_pos_x, abs_pos_y));
    window->draw(ghost);
#endif
}
