#include "../defines.h"
#include "../models/GamePlay.h"

#if USE_SFML
#include "SFML/Audio.hpp"
#include <chrono>
#include <mutex>
#include <thread>
#endif

void audio_loop(models::GamePlay* gameplay);