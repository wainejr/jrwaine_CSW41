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

void ViewGamePlay::draw(sf::RenderWindow* window)
{
    this->view_labyrinth.draw(window);
    this->view_ghosts[0].draw(window);
    this->view_ghosts[1].draw(window);
    this->view_ghosts[2].draw(window);
    this->view_ghosts[3].draw(window);
    this->view_pac.draw(window);

    // end the current frame
    window->display();
}