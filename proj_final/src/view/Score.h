#include "../models/Score.h"
#include "Base.h"

#ifndef _VIEW_SCORE_H_
#define _VIEW_SCORE_H_

namespace view {
class ViewScore : public Base {
public:
    ViewScore(models::Score* score);

    void draw(sf::RenderWindow* window);
    models::Score* score;
};
}
#endif