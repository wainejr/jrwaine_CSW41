#include "Agent.h"

using namespace view;

ViewAgent::ViewAgent(models::Agent* agent)
    : agent(agent)
{
}

void ViewAgent::draw_agent(DrawContext* context, unsigned long color)
{
    float abs_pos_x, abs_pos_y;
    float center_pos_x = this->agent->pos.x + 0.5f;
    float center_pos_y = this->agent->pos.y + 0.5f;
    globals::get_normalized_pos(center_pos_x, center_pos_y, &abs_pos_x, &abs_pos_y);

    GrContextForegroundSet(context, ClrBlack);
    tRectangle black_background { (int16_t)(floor(abs_pos_x - globals::TILE_SIZE / 2)),
        (int16_t)(floor(abs_pos_y - globals::TILE_SIZE / 2)),
        (int16_t)(ceil(abs_pos_x + globals::TILE_SIZE / 2)),
        (int16_t)(ceil(abs_pos_y + globals::TILE_SIZE / 2)) };

    if (this->agent->direction.x == -1) {
        black_background.i16XMax += 1;
    } else if (this->agent->direction.x == 1) {
        black_background.i16XMin -= 1;
    } else if (this->agent->direction.y == 1) {
        black_background.i16YMax += 1;
    } else if (this->agent->direction.y == -1) {
        black_background.i16YMin -= 1;
    }

    // GrRectFill(context, &black_background);

    GrContextForegroundSet(context, color);
    GrCircleFill(context, (int32_t)abs_pos_x, (int32_t)abs_pos_y, (int32_t)globals::PACMAN_RADIUS);
}
