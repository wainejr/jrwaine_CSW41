#include "Game.h"

using namespace view;

ViewGame::ViewGame(models::Game* game)
    : game(game)
    , view_gameplay(&game->gameplay)
{
}

void ViewGame::draw_score(DrawContext* context)
{
    int score = (int)round((double)this->game->gameplay.score.curr_score);
    std::string text = "Score: ";
    text += std::to_string(score);

#if USE_SFML
    sf::Text text_score;

    text_score.setString(str_score);
    text_score.setPosition(sf::Vector2f(128 / 2 - 30, 128 / 2 - 5));

    context->draw(text_score);
#else
    GrContextForegroundSet(context, ClrWhite);
    GrStringDraw(context, text.c_str(), (int32_t)text.size(), 30,
        (context->psFont->ui8Height + 2) * 6, true);
#endif
}

void ViewGame::draw_menu(DrawContext* context)
{
    GrContextForegroundSet(context, ClrWhite);
    GrStringDraw(context, "> New Game", -1, 0,
        (context->psFont->ui8Height + 2) * 5, true);
    GrStringDraw(context, "Press Button", -1, 30,
        (context->psFont->ui8Height + 2) * 10, true);
}

void ViewGame::clean_screen(DrawContext* context)
{
    // context->clear(sf::Color::Black);
    tRectangle screen { 0, 0, globals::RESOLUTION_X, globals::RESOLUTION_Y };
    GrContextForegroundSet(context, ClrBlack);
    GrRectFill(context, &screen);
}

void ViewGame::draw(DrawContext* context)
{
    // clear the window with black color
    // context->clear(sf::Color::Black);
    // tRectangle screen{0, 0, 128, 128};
    // GrContextForegroundSet(context, ClrBlack);
    // GrRectFill(context, &screen);

    switch (game->curr_state) {
    case models::GlobalStates::PLAYING:
        this->view_gameplay.draw(context);
        break;
    case models::GlobalStates::MENU:
        this->view_gameplay.view_labyrinth.maze_drawed = false;
        this->draw_menu(context);
        break;
    case models::GlobalStates::SHOWING_SCORE:
        this->view_gameplay.view_labyrinth.maze_drawed = false;
        this->draw_score(context);
        break;
    default:
        break;
    }
    GrFlush(context);
}
