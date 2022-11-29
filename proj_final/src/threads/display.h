#include "../defines.h"
#include "../models/Game.h"
#include "../view/Game.h"

#if USE_SFML
#include "SFML/Graphics.hpp"
#include <chrono>
#include <mutex>
#include <thread>
#endif

#ifndef _THREADS_DISPLAY_H_
#define _THREADS_DISPLAY_H_

#if USE_SFML
void display_loop(models::Game* game);
#else
void display_loop(UINT id);
#endif

#endif