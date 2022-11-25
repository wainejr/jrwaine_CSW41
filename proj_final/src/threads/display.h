#include "../defines.h"
#include "../models/GamePlay.h"
#include "../view/GamePlay.h"

#if USE_SFML
#include "SFML/Graphics.hpp"
#include <chrono>
#include <mutex>
#include <thread>
#endif

#ifndef _THREADS_DISPLAY_H_
#define _THREADS_DISPLAY_H_

#if USE_SFML
void display_loop(models::GamePlay* gameplay);
#else
void display_loop(UINT id);
#endif

#endif