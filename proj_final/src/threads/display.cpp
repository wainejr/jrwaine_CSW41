#include "display.h"

#if USE_SFML

void handle_pacman_direction(models::GamePlay* gameplay, sf::Keyboard::Key code)
{
    switch (code) {
    case sf::Keyboard::Down:
        gameplay->update_pacman_direction(models::consts::DOWN);
        break;
    case sf::Keyboard::Left:
        gameplay->update_pacman_direction(models::consts::LEFT);
        break;
    case sf::Keyboard::Right:
        gameplay->update_pacman_direction(models::consts::RIGHT);
        break;
    case sf::Keyboard::Up:
        gameplay->update_pacman_direction(models::consts::UP);
        break;
    default:
        break;
    }
}

void display_loop(models::GamePlay* gameplay)
{
    view::ViewGamePlay view_gameplay(gameplay);
    sf::RenderWindow window(sf::VideoMode(view::globals::RESOLUTION_X, view::globals::RESOLUTION_Y), "My window");

    while (window.isOpen()) {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::KeyPressed) {
                handle_pacman_direction(gameplay, event.key.code);
            } else if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        if (gameplay->gamestate == models::GAME_STATE_ENDED) {
            break;
        }
        view_gameplay.draw(&window);

        std::this_thread::sleep_for(std::chrono::milliseconds((int)(1000 / view::globals::DESIRED_FPS)));
    }
}
#else
void display_loop(ULONG id)
{
}

#endif