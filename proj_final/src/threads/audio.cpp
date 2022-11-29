#include "audio.h"

void audio_loop(models::Game* game)
{
    sf::Sound sound;
    sf::SoundBuffer buffer_normal;
    sf::SoundBuffer buffer_super;

    const int SAMPLES_SIZE = 100000;
    std::vector<sf::Int16> samples_normal(SAMPLES_SIZE);
    std::vector<sf::Int16> samples_super(SAMPLES_SIZE);
    for (int i = 0; i < SAMPLES_SIZE; i++) {
        samples_normal[i] = 4000;
        samples_super[i] = 15000;
    }
    buffer_normal.loadFromSamples(&samples_normal[0], SAMPLES_SIZE, 1, 10000);
    buffer_super.loadFromSamples(&samples_super[0], SAMPLES_SIZE, 1, 10000);

    sound.setBuffer(buffer_normal);

    while (true) {
        switch (game->curr_state) {
        case models::GlobalStates::PLAYING:
            if (game->gameplay.pac.state == models::PacmanState::NORMAL) {
                if (sound.getBuffer() != &buffer_normal)
                    sound.setBuffer(buffer_normal);
            } else if (game->gameplay.pac.state == models::PacmanState::SUPER) {
                if (sound.getBuffer() != &buffer_super)
                    sound.setBuffer(buffer_super);
            }
            sound.play();
            break;
        default:
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            break;
        }
    }
}