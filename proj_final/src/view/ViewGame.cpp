#include "Game.h"

using namespace view;

ViewGame::ViewGame(models::Game* game)
    : game(game)
    , view_gameplay(&game->gameplay)
{
}

void ViewGame::update_view_gameplay()
{
    this->view_gameplay = ViewGamePlay(&game->gameplay);
}

void ViewGame::draw_score(DrawContext* context)
{
#if USE_SFML
    sf::Text text_score;

    std::string str_score = "Score: ";
    str_score += std::to_string((int)(this->game->gameplay.score.curr_score));

    text_score.setString(str_score);
    text_score.setPosition(sf::Vector2f(128 / 2 - 30, 128 / 2 - 5));

    context->draw(text_score);
#else
    
    
#endif
}

void ViewGame::draw_menu(DrawContext* context)
{
    printf("drawing menu\n");
    // sf::Text text_new_game;

    // text_new_game.setString("New Game");
    // text_new_game.setPosition(sf::Vector2f((128-60)/2, (128-30)/2));

    // sf::RectangleShape rect(sf::Vector2f(10.0f, 10.0f));
    // rect.setFillColor(sf::Color(10, 10, 10));
    // rect.setOutlineColor(sf::Color(0, 255, 255, 1));
    // rect.setOutlineThickness(10);
    // rect.setPosition(sf::Vector2f(10.0f, 10.0f));

    // window->draw(rect);
    // window->draw(text_new_game);

    float abs_pos_x, abs_pos_y;
    float center_pos_x = 10 + 0.5;
    float center_pos_y = 10 + 0.5;
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

void ViewGame::draw(DrawContext* context)
{
    // clear the window with black color
    // context->clear(sf::Color::Black);

    switch (game->curr_state) {
    case models::GlobalStates::PLAYING:
        this->view_gameplay.draw(context);
        break;
    case models::GlobalStates::MENU:
        this->draw_menu(context);
        break;
    case models::GlobalStates::SHOWING_SCORE:
        this->draw_score(context);
        break;
    default:
        break;
    }
}
