#include "../defines.h"
#include "../models/GhostControl.h"
#include "../models/Game.h"

#if USE_SFML
#include <chrono>
#include <stdlib.h>
#include <thread>
#include <time.h>
#include <vector>


void control_ghost_loop(models::GamePlay* gameplay, models::Ghost* ghost, int random_seed);
#else

#define THREAD_GHOST_PERIOD         THREAD_PERIOD(5*models::consts::STATE_UPDATE_SEC_INTERVAL)

extern TX_THREAD g_thread_ghosts[4];
extern TX_BYTE_POOL g_byte_pool;
extern models::Game g_game;

void    control_ghost_loop(ULONG ghost_idx);
void    initialize_threads_control_ghosts();
#endif


