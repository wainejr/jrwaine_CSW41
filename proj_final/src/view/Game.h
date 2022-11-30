#include "../models/Game.h"
#include "Base.h"
#include "GamePlay.h"

#ifndef _VIEW_GAME_H_
#define _VIEW_GAME_H_

namespace view {
class ViewGame : public Base {
    void draw_score(DrawContext* context);
    void draw_menu(DrawContext* context);

public:
    ViewGame(models::Game* game);
    models::Game* game;
    ViewGamePlay view_gameplay;

    void draw(DrawContext* context);
    void update_view_gameplay();
};
}
#endif