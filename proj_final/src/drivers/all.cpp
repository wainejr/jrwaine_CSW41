#include "all.h"

using namespace drivers;

void drivers::setup_all(){
    setup_button();
    setup_buzzer();
    setup_joystick();
    setup_LCD();
}