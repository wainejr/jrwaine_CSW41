#include "PacMan.h"

using namespace view;

ViewPacMan::ViewPacMan(models::PacMan* pac)
    : pac(pac)
{
}

void ViewPacMan::draw(sf::RenderWindow* window)
{
    float abs_pos_x, abs_pos_y;
    float center_pos_x = this->pac->pos.x + 0.5;
    float center_pos_y = this->pac->pos.y + 0.5;
    globals::get_normalized_pos(center_pos_x, center_pos_y, &abs_pos_x, &abs_pos_y);
    abs_pos_x = abs_pos_x - globals::PACMAN_RADIUS;
    abs_pos_y = abs_pos_y - globals::PACMAN_RADIUS;

#if USE_SFML
    sf::CircleShape pac(globals::PACMAN_RADIUS);

    pac.setPosition(sf::Vector2f(abs_pos_x, abs_pos_y));
    pac.setFillColor(sf::Color(255, 255, 0));

    window->draw(pac);
#endif
}