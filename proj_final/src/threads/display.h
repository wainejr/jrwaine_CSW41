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

#define THREAD_DISPLAY_PERIOD THREAD_PERIOD(1.0f / view::globals::DESIRED_FPS)

extern TX_THREAD g_thread_display;
extern TX_TIMER g_timer_display;
extern TX_BYTE_POOL g_byte_pool;

extern models::Game g_game;
extern view::ViewGame g_view_game;
extern tContext g_context;

void display_loop(UINT id);
void timer_display_expiration(ULONG expiration_input);
void initialize_thread_display();

#endif

#endif