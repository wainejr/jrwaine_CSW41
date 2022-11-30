#include "PacMan.h"

using namespace view;

ViewPacMan::ViewPacMan(models::PacMan* pac)
    : pac(pac)
{
}

void ViewPacMan::draw(DrawContext* context)
{
    float abs_pos_x, abs_pos_y;
    float center_pos_x = this->pac->pos.x + 0.5f;
    float center_pos_y = this->pac->pos.y + 0.5f;
    globals::get_normalized_pos(center_pos_x, center_pos_y, &abs_pos_x, &abs_pos_y);

#if USE_SFML
    abs_pos_x = abs_pos_x - globals::PACMAN_RADIUS;
    abs_pos_y = abs_pos_y - globals::PACMAN_RADIUS;
    
    sf::CircleShape pac(globals::PACMAN_RADIUS);

    pac.setPosition(sf::Vector2f(abs_pos_x, abs_pos_y));
    pac.setFillColor(sf::Color(255, 255, 0));

    window->draw(pac);
#else
    GrContextForegroundSet(context, ClrYellow);     
    GrCircleFill(context, (int32_t)abs_pos_x, (int32_t)abs_pos_y, (int32_t)globals::PACMAN_RADIUS);
#endif
}
