#include "GamePlay.h"

using namespace view;

ViewGamePlay::ViewGamePlay(models::GamePlay* gameplay)
    : view_pac(&gameplay->pac)
    , view_labyrinth(&gameplay->lab)
    , view_ghosts { ViewGhost(&gameplay->ghosts[0]),
        ViewGhost(&gameplay->ghosts[1]),
        ViewGhost(&gameplay->ghosts[2]),
        ViewGhost(&gameplay->ghosts[3]) }
{
    this->gameplay = gameplay;
}

void ViewGamePlay::draw(DrawContext* context)
{
    this->view_labyrinth.draw(context);
    this->view_ghosts[0].draw(context);
    this->view_ghosts[1].draw(context);
    this->view_ghosts[2].draw(context);
    this->view_ghosts[3].draw(context);
    this->view_pac.draw(context);
    
#if USE_SFML
    // end the current frame
    window->display();
#endif
}