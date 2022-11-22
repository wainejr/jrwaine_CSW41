#include "GamePlay.h"

models::GamePlay::GamePlay()
{
    this->lab = Labyrinth();
    this->pac = PacMan();

    this->ghosts[0] = Ghost(GhostColors::RED);
    this->ghosts[1] = Ghost(GhostColors::YELLOW);
    this->ghosts[2] = Ghost(GhostColors::BLUE);
    this->ghosts[3] = Ghost(GhostColors::PINK);

    this->score = Score();
}