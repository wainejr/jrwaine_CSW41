#include "../defines.h"
#include "../models/Game.h"

#if USE_SFML
#include <chrono>
#include <thread>
#endif

#ifndef _THREADS_UPDATE_STATE_H_
#define _THREADS_UPDATE_STATE_H_

#if USE_SFML
void update_state_loop(models::Game* game);
#else
void update_state_loop(UINT id);
#endif

#endif