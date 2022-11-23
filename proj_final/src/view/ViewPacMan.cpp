#include "PacMan.h"

using namespace view;

ViewPacMan::ViewPacMan(models::PacMan* pac)
    : pac(pac)
{
}

void ViewPacMan::draw(sf::RenderWindow* window)
{
    float abs_pos_x, abs_pos_y;
    globals::get_normalized_pos(this->pac->pos.x, this->pac->pos.y, &abs_pos_x, &abs_pos_y);
    abs_pos_x = abs_pos_x - globals::PACMAN_RADIUS;
    abs_pos_y = abs_pos_y - globals::PACMAN_RADIUS;

#if USE_SFML
    sf::CircleShape pac(globals::PACMAN_RADIUS);

    pac.setPosition(sf::Vector2f(abs_pos_x, abs_pos_y));
    pac.setFillColor(sf::Color(255, 255, 0));

    window->draw(pac);
#endif
}
