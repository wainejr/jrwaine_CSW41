#include "all.h"

using namespace drivers;

void drivers::setup_all(tContext* pContext)
{
    setup_button();
    setup_buzzer();
    setup_joystick();
    setup_LCD(pContext);
}