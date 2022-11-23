// #include "models/GamePlay.h"
// #include "models/GameState.h"

#include <chrono>
#include <thread>

#include "models/GamePlay.h"
#include "view/GamePlay.h"
#include <SFML/Graphics.hpp>

int main()
{
    models::GamePlay gameplay;
    view::ViewGamePlay view_gamplay(&gameplay);
    sf::RenderWindow window(sf::VideoMode(view::globals::RESOLUTION_X, view::globals::RESOLUTION_Y), "My window");

    while (window.isOpen()) {
        gameplay.update();
        view_gamplay.draw(&window);
        std::this_thread::sleep_for(std::chrono::milliseconds(1000 / 10));
    }

    // create the window

    // // run the program as long as the window is open
    // while (window.isOpen())
    // {
    //     // check all the window's events that were triggered since the last iteration of the loop
    //     sf::Event event;
    //     while (window.pollEvent(event))
    //     {
    //         // "close requested" event: we close the window
    //         if (event.type == sf::Event::Closed)
    //             window.close();
    //     }

    //     // clear the window with black color
    //     window.clear(sf::Color::Black);

    //     // draw everything here...
    //     // window.draw(...);

    //     // end the current frame
    //     window.display();
    // }

    return 0;
}