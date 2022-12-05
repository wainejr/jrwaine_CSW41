#include "button.h"
#include "../models/Game.h"

using namespace drivers;

extern models::Game g_game;

void intButtonGame(void){

    GPIOIntClear(GPIO_PORTL_BASE, GPIO_INT_PIN_2);
    if(g_game.curr_state == models::GlobalStates::MENU){
        g_game.into_playing();
    }
}

void drivers::setup_button()
{
    // Configure button port
    // Enable GPIO Port L
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOL);
    while (!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOL)){}

    // Configure pin L2 for GPIO input
    GPIOPinTypeGPIOInput(GPIO_PORTL_BASE, GPIO_PIN_2);
}

void drivers::setup_interruption()
{
    // Register Interrupt function
    IntRegister(INT_GPIOL, intButtonGame);
    // Enable peripheral interrupts
    GPIOIntEnable(GPIO_PORTL_BASE, GPIO_INT_PIN_2);
    // Enable interrupts in NVIC
    IntEnable(INT_GPIOL);
    IntMasterEnable();
}

bool drivers::get_button_pressed()
{
    int val = GPIOPinRead(GPIO_PORTL_BASE, GPIO_PIN_2);
    return !((bool)val);
}