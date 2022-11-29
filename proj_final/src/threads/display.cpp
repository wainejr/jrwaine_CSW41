#include "display.h"

#if USE_SFML

void handle_action(models::Game* game, view::ViewGame* view_game, sf::Keyboard::Key code)
{
    switch (game->curr_state) {
    case models::GlobalStates::PLAYING:
        switch (code) {
        case sf::Keyboard::Down:
            game->gameplay.update_pacman_direction(models::consts::DOWN);
            break;
        case sf::Keyboard::Left:
            game->gameplay.update_pacman_direction(models::consts::LEFT);
            break;
        case sf::Keyboard::Right:
            game->gameplay.update_pacman_direction(models::consts::RIGHT);
            break;
        case sf::Keyboard::Up:
            game->gameplay.update_pacman_direction(models::consts::UP);
            break;
        default:
            break;
        }
        break;
    case models::GlobalStates::MENU:
        switch (code) {
        case sf::Keyboard::Enter:
            game->into_playing();
            view_game->update_view_gameplay();
            break;
        default:
            break;
        }
        break;
    default:
        break;
    }
}

void display_loop(models::Game* game)
{
    view::ViewGame view_game(game);
    sf::RenderWindow window(sf::VideoMode(view::globals::RESOLUTION_X, view::globals::RESOLUTION_Y), "My window");

    while (true) {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::KeyPressed) {
                handle_action(view_game.game, &view_game, event.key.code);
            } else if (event.type == sf::Event::Closed) {
                window.close();
                break;
            }
        }
        view_game.draw(&window);

        std::this_thread::sleep_for(std::chrono::milliseconds((int)(1000 / view::globals::DESIRED_FPS)));
    }
}
#else
void display_loop(ULONG id)
{
}

#endif