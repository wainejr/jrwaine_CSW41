#include "Labirynth.h"

using namespace view;

ViewLabyrinth::ViewLabyrinth(models::Labyrinth* lab)
    : lab(lab)
{
}

void ViewLabyrinth::draw(sf::RenderWindow* window)
{
    this->draw_labyrinth_maze(window);
    for (int i = 0; i < 28; i++) {
        for (int j = 0; j < 31; j++) {
            models::TilesTypes tl = lab->lab[j][i];
            if (tl == models::TilesTypes::SMALL_BALL) {
                this->draw_small_ball(window, misc::Vector<int>(i, j));
            } else if (tl == models::TilesTypes::SUPER_BALL) {
                this->draw_big_ball(window, misc::Vector<int>(i, j));
            }
        }
    }
}

void ViewLabyrinth::draw_maze_square(sf::RenderWindow* window, misc::Vector<int> pos, models::TilesTypes tl)
{
    float abs_pos_x, abs_pos_y;
    globals::get_normalized_pos((float)pos.x, (float)pos.y, &abs_pos_x, &abs_pos_y);

#if USE_SFML
    sf::RectangleShape square(sf::Vector2f(globals::TILE_SIZE, globals::TILE_SIZE));
    if (tl == models::TilesTypes::WALL) {
        square.setFillColor(sf::Color(50, 50, 200));
    } else if (tl == models::TilesTypes::TUNNEL) {
        square.setFillColor(sf::Color(200, 150, 220));
    }
    square.setPosition(sf::Vector2f(abs_pos_x, abs_pos_y));
    window->draw(square);
#endif
}

void ViewLabyrinth::draw_labyrinth_maze(sf::RenderWindow* window)
{
    for (int i = 0; i < 28; i++) {
        for (int j = 0; j < 31; j++) {
            models::TilesTypes tl = this->lab->lab[j][i];
            if (tl == models::TilesTypes::TUNNEL || tl == models::TilesTypes::WALL) {
                this->draw_maze_square(window, misc::Vector<int>(i, j), tl);
            }
        }
    }
}

void ViewLabyrinth::draw_small_ball(sf::RenderWindow* window, misc::Vector<int> pos_ball)
{
    float abs_pos_x, abs_pos_y;
    globals::get_normalized_pos((float)pos_ball.x, (float)pos_ball.y, &abs_pos_x, &abs_pos_y);

#if USE_SFML
    // sf::RenderWindow* winddow = &this->window;
    sf::RectangleShape small_ball(sf::Vector2f(globals::SMALL_BALL_SIZE, globals::SMALL_BALL_SIZE));
    small_ball.setFillColor(sf::Color(255, 255, 255));

    // Sum one pixel position to tile
    abs_pos_x = abs_pos_x + 1;
    abs_pos_y = abs_pos_y + 1;

    small_ball.setPosition(abs_pos_x, abs_pos_y);
    window->draw(small_ball);
#endif
}

void ViewLabyrinth::draw_big_ball(sf::RenderWindow* window, misc::Vector<int> pos_ball)
{
    float abs_pos_x, abs_pos_y;
    globals::get_normalized_pos((float)pos_ball.x, (float)pos_ball.y, &abs_pos_x, &abs_pos_y);

#if USE_SFML
    // sf::RenderWindow* winddow = &this->window;
    sf::RectangleShape big_ball(sf::Vector2f(globals::BIG_BALL_SIZE, globals::BIG_BALL_SIZE));
    big_ball.setFillColor(sf::Color(255, 255, 255));

    // Sum one pixel position to tile
    abs_pos_x = abs_pos_x + 1;
    abs_pos_y = abs_pos_y + 1;

    big_ball.setPosition(abs_pos_x, abs_pos_y);
    window->draw(big_ball);
#endif
}