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
    models::GlobalStates last_state = g_game.curr_state;
    while (true) {
        if(g_game.curr_state != last_state){
          g_view_game.clean_screen(&g_context);
          last_state = g_game.curr_state;
        }
        g_view_game.draw(&g_context);
        tx_thread_suspend(&g_thread_display);
    }
}

void timer_display_expiration(ULONG expiration_input){
    tx_thread_resume(&g_thread_display);
}

void initialize_thread_display(){
    /* Memory pointer */
    CHAR *pointer = (CHAR*)TX_NULL;

    /* Allocate the stack for display thread  */
    tx_byte_allocate(&g_byte_pool, (VOID **) &pointer, STACK_SIZE, TX_NO_WAIT);

    /* Create the thread for display  */
    tx_thread_create(&g_thread_display, "thread display", display_loop, 0, pointer, 
        STACK_SIZE, 0, 0, 0, TX_AUTO_START);

    /* Create the timer for display */
    tx_timer_create(&g_timer_display, "timer display", timer_display_expiration, 1,
                    THREAD_DISPLAY_PERIOD, THREAD_DISPLAY_PERIOD, TX_AUTO_ACTIVATE);
}

#endif
