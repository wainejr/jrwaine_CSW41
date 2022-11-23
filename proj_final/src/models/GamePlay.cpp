#include "GamePlay.h"

using namespace models;

GamePlay::GamePlay()
{
    this->pac = PacMan();

    this->ghosts[0] = Ghost(GhostColors::RED);
    this->ghosts[1] = Ghost(GhostColors::YELLOW);
    this->ghosts[2] = Ghost(GhostColors::BLUE);
    this->ghosts[3] = Ghost(GhostColors::PINK);

    Ghost* ghosts_ref[4] = { &this->ghosts[0], &this->ghosts[1], &this->ghosts[2], &this->ghosts[3] };

    this->lab = Labyrinth();

    this->score = Score();
}

void correct_agent_position(Agent* a) {};

misc::Vector<int> get_pos_quadrant(misc::Vector<float> pos)
{
    return misc::Vector<int>(0, 0);
}

void GamePlay::update_positions()
{
    this->pac.update_position();
    correct_agent_position(&this->pac);
    for (int i = 0; i < 4; i++) {
        this->ghosts[i].update_position();
        correct_agent_position(&this->ghosts[i]);
    }
}

bool GamePlay::check_collision(PacMan* pac, Ghost* ghost)
{
    return false;
}

void GamePlay::update_pacman_state()
{
}

void GamePlay::update_ghosts_states()
{
}

UpdateStatus::myEnum GamePlay::update()
{

    return UpdateStatus::GAME_CONTINUE;
}