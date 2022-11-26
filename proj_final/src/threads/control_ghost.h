#include "../models/GhostControl.h"
#include <chrono>
#include <stdlib.h>
#include <thread>
#include <time.h>
#include <vector>

void control_ghost_loop(models::GamePlay* gameplay, models::Ghost* ghost, int random_seed);
