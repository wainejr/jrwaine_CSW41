#include "globals.h"

#ifndef _VIEW_BASE_H_
#define _VIEW_BASE_H_

#include <chrono>
#include <thread>

#include <SFML/Graphics.hpp>

namespace view {
class Base {
public:
    virtual void draw(sf::RenderWindow* window) = 0;
};
}
#endif