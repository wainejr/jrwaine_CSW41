#include "Labirynth.h"

using namespace view;

ViewLabyrinth::ViewLabyrinth(models::Labyrinth* lab)
    : lab(lab)
    , maze_drawed(false)
{
}

void ViewLabyrinth::draw(DrawContext* context)
{
    if (!this->maze_drawed) {
        this->draw_labyrinth_maze(context);
        this->maze_drawed = true;
    }
    /*
    for (int i = 0; i < 28; i++) {
        for (int j = 0; j < 31; j++) {
            models::TilesTypes tl = lab->lab[j][i];
            if (tl == models::TilesTypes::SMALL_BALL) {
                this->draw_ball(context, misc::Vector<int>(i, j), false);
            } else if (tl == models::TilesTypes::SUPER_BALL) {
                this->draw_ball(context, misc::Vector<int>(i, j), true);
            } else if(tl == models::TilesTypes::TUNNEL){
                this->draw_maze_square(context, misc::Vector<int>(i, j), tl);
            }
        }
    }
    */
}

void ViewLabyrinth::draw_maze_square(DrawContext* context, misc::Vector<int> pos, models::TilesTypes tl)
{
    switch (tl) {
    case models::TilesTypes::PATH:
        GrContextForegroundSet(context, ClrBlack);
        break;
    case models::TilesTypes::WALL:
        GrContextForegroundSet(context, ClrPurple);
        break;
    case models::TilesTypes::TUNNEL:
        GrContextForegroundSet(context, ClrBeige);
        break;
    default:
        return;
    }

    float abs_pos_x, abs_pos_y;
    globals::get_normalized_pos((float)pos.x, (float)pos.y, &abs_pos_x, &abs_pos_y);

    tRectangle rect {
        (int16_t)abs_pos_x,
        (int16_t)abs_pos_y,
        (int16_t)(abs_pos_x + globals::TILE_SIZE),
        (int16_t)(abs_pos_y + globals::TILE_SIZE)
    };
    GrRectFill(context, &rect);
}

void ViewLabyrinth::draw_labyrinth_maze(DrawContext* context)
{
    for (int i = 0; i < 28; i++) {
        for (int j = 0; j < 31; j++) {
            models::TilesTypes tl = this->lab->lab[j][i];
            draw_tile(context, misc::Vector<int>(i, j), tl);
        }
    }
}

void ViewLabyrinth::draw_ball(DrawContext* context, misc::Vector<int> pos_ball, bool is_big)
{
    this->draw_maze_square(context, pos_ball, models::TilesTypes::PATH);
    float abs_pos_x, abs_pos_y;
    globals::get_normalized_pos((float)pos_ball.x, (float)pos_ball.y, &abs_pos_x, &abs_pos_y);

    // Sum one pixel position to tile
    abs_pos_x = abs_pos_x + 1;
    abs_pos_y = abs_pos_y + 1;

    GrContextForegroundSet(context, ClrWhite);

    tRectangle rect {
        (int16_t)(abs_pos_x),
        (int16_t)(abs_pos_y),
        (int16_t)(abs_pos_x + (is_big ? 2 : 1)),
        (int16_t)(abs_pos_y + (is_big ? 2 : 1))
    };
    GrRectFill(context, &rect);
}

void ViewLabyrinth::update_near_tiles(DrawContext* context, misc::Vector<int> tile_pos)
{
    misc::Vector<int> tile_up { tile_pos.x, misc::remainder(tile_pos.y - 1, models::consts::MAZE_SIZE_Y) };
    misc::Vector<int> tile_down { tile_pos.x, misc::remainder(tile_pos.y + 1, models::consts::MAZE_SIZE_Y) };
    misc::Vector<int> tile_right { misc::remainder(tile_pos.x + 1, models::consts::MAZE_SIZE_X), tile_pos.y };
    misc::Vector<int> tile_left { misc::remainder(tile_pos.x - 1, models::consts::MAZE_SIZE_X), tile_pos.y };

    this->update_tile(context, tile_pos);
    this->update_tile(context, tile_up);
    this->update_tile(context, tile_down);
    this->update_tile(context, tile_right);
    this->update_tile(context, tile_left);
}

void ViewLabyrinth::draw_tile(DrawContext* context, misc::Vector<int> tile_pos, models::TilesTypes tl)
{
    switch (tl) {
    case models::TilesTypes::PATH:
        this->draw_maze_square(context, tile_pos, tl);
        break;
    case models::TilesTypes::TUNNEL:
        this->draw_maze_square(context, tile_pos, tl);
        break;
    case models::TilesTypes::WALL:
        this->draw_maze_square(context, tile_pos, tl);
        break;
    case models::TilesTypes::SUPER_BALL:
        this->draw_ball(context, tile_pos, true);
        break;
    case models::TilesTypes::SMALL_BALL:
        this->draw_ball(context, tile_pos, false);
        break;
    default:
        break;
    }
}

void ViewLabyrinth::update_tile(DrawContext* context, misc::Vector<int> tile_pos)
{
    models::TilesTypes tl = this->lab->get_tile(tile_pos.x, tile_pos.y);

    float abs_pos_x, abs_pos_y;
    globals::get_normalized_pos((float)tile_pos.x, (float)tile_pos.y, &abs_pos_x, &abs_pos_y);

    // if(tl == models::WALL){
    //     return;
    // }
    this->draw_tile(context, tile_pos, tl);
}
