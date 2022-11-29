#include "../defines.h"
#include "../models/Game.h"

#if USE_SFML
#include "SFML/Audio.hpp"
#include <chrono>
#include <mutex>
#include <thread>
#endif

void audio_loop(models::Game* game);