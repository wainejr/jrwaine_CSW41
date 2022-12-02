#include "../defines.h"
#include "../drivers/all.h"
#include "../models/Game.h"


#ifndef _THREADS_ACTIONS_H_
#define _THREADS_ACTIONS_H_

// Check actions every 0.1s (10Hz)
#define THREAD_ACTIONS_PERIOD THREAD_PERIOD(0.1f)

extern TX_THREAD g_thread_actions;
extern TX_TIMER g_timer_actions;
extern TX_BYTE_POOL g_byte_pool;

extern models::Game g_game;

void actions_loop(UINT id);
void timer_actions_expiration(ULONG expiration_input);
void initialize_thread_actions();

#endif