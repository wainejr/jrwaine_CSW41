#include "Game.h"

using namespace models;

Game::Game()
{
    this->curr_state = GlobalStates::MENU;
    this->gameplay = GamePlay();
}

void Game::into_playing()
{
    this->gameplay = GamePlay();
    this->curr_state = GlobalStates::PLAYING;
}

void Game::into_showing_score()
{
    this->curr_state = GlobalStates::SHOWING_SCORE;
}

void Game::into_menu()
{
    this->curr_state = GlobalStates::MENU;
}
