#include "../models/Labyrinth.h"
#include "Base.h"

#ifndef _VIEW_LABYRINTH_H_
#define _VIEW_LABYRINTH_H_

namespace view {
class ViewLabyrinth : public Base {
    void draw_labyrinth_maze(sf::RenderWindow* window);
    void draw_maze_square(sf::RenderWindow* window, misc::Vector<int> pos, models::TilesTypes tl);
    void draw_small_ball(sf::RenderWindow* window, misc::Vector<int> pos_ball);
    void draw_big_ball(sf::RenderWindow* window, misc::Vector<int> pos_ball);

public:
    ViewLabyrinth(models::Labyrinth* lab);

    models::Labyrinth* lab;
    void draw(sf::RenderWindow* window);
};
}
#endif // !_VIEW_LABYRINTH_H_
