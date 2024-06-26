#include "../defines.h"
#include "../models/Game.h"
#include "../drivers/button.h"

#ifndef _THREADS_UPDATE_STATE_H_
#define _THREADS_UPDATE_STATE_H_


#define THREAD_UPDATE_STATE_PERIOD THREAD_PERIOD(models::consts::STATE_UPDATE_SEC_INTERVAL)

extern TX_THREAD g_thread_state;
extern TX_THREAD g_thread_ghosts[4];

extern TX_TIMER g_timer_state;

extern TX_BYTE_POOL g_byte_pool;

extern models::Game g_game;

void thread_update_state(ULONG id);
void timer_state_expiration(ULONG expiration_input);
void initialize_thread_update_state();

#endif
