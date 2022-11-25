// #include "models/GamePlay.h"
// #include "models/GameState.h"

#include <SFML/Graphics.hpp>
#include <chrono>
#include <mutex>
#include <thread>

#include "models/GamePlay.h"
#include "threads/audio.h"
#include "threads/display.h"
#include "threads/update_state.h"
#include "view/GamePlay.h"

int main()
{
    models::GamePlay gameplay;

    std::thread t_display(display_loop, &gameplay);
    std::thread t_update_state(update_state_loop, &gameplay);
    std::thread t_audio(audio_loop, &gameplay);

    while (true) {
        std::this_thread::sleep_for(std::chrono::milliseconds(150));
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