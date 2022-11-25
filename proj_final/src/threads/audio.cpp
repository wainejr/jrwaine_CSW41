#include "audio.h"

void audio_loop(models::GamePlay* gameplay)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));

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
    buffer_normal.loadFromSamples(&samples_normal[0], SAMPLES_SIZE, 1, 44100);
    buffer_super.loadFromSamples(&samples_super[0], SAMPLES_SIZE, 1, 44100);

    sound.setBuffer(buffer_normal);

    while (true) {
        sound.play();
        if (gameplay->pac.state == models::PacmanState::NORMAL) {
            sound.setBuffer(buffer_normal);
        } else if (gameplay->pac.state == models::PacmanState::SUPER) {
            sound.setBuffer(buffer_super);
        } else {
            break;
        }
    }
}