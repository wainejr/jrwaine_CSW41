#include "Game.h"

using namespace models;


Game::Game()
{
    this->curr_state = GlobalStates::MENU;
    this->gameplay = GamePlay();
}

GlobalStates Game::state_machine(){
    switch (this->curr_state)
    {
    case GlobalStates::PLAYING:
        /* code */
        break;
    case GlobalStates::MENU:
        /* code */
        break;
    case GlobalStates::SHOWING_SCORE:
        /* code */
        break;
    default:
        break;
    }
}


void Game::loop_playing(){
    this->gameplay = GamePlay();
    this->curr_state = GlobalStates::PLAYING;
}

void Game::loop_showing_score(){
    this->gameplay = GamePlay();
    this->curr_state = GlobalStates::PLAYING;
}

void Game::loop_menu(){
    this->gameplay = GamePlay();
    this->curr_state = GlobalStates::PLAYING;
}

void Game::into_playing(){
    this->gameplay = GamePlay();
    this->curr_state = GlobalStates::PLAYING;
}

void Game::into_showing_score(){
    this->curr_state = GlobalStates::SHOWING_SCORE;
}

void Game::into_menu(){
    this->curr_state = GlobalStates::MENU;
}
