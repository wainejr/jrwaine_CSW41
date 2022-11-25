#include "../defines.h"
#include "../models/GamePlay.h"

#if USE_SFML
#include <chrono>
#include <thread>
#endif

#ifndef _THREADS_UPDATE_STATE_H_
#define _THREADS_UPDATE_STATE_H_

#if USE_SFML
void update_state_loop(models::GamePlay* gameplay);
#else
void update_state_loop(UINT id);
#endif

#endif