#include "../defines.h"
#include "../models/Game.h"
#include "../models/GhostControl.h"

#ifndef _THREADS_CONTROL_GHOST_H_
#define _THREADS_CONTROL_GHOST_H_

#define THREAD_GHOST_PERIOD THREAD_PERIOD(5 * models::consts::STATE_UPDATE_SEC_INTERVAL)

extern TX_THREAD g_thread_ghosts[4];
extern TX_BYTE_POOL g_byte_pool;
extern models::Game g_game;

void control_ghost_loop(ULONG ghost_idx);
void initialize_threads_control_ghosts();
#endif
