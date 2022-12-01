#include "button.h"

using namespace drivers;

void drivers::setup_button()
{
    // Configure button port
    // Enable GPIO Port L
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOL);
    while (!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOL))
        ;

    // Configure pin L2 for GPIO input
    GPIOPinTypeGPIOInput(GPIO_PORTL_BASE, GPIO_PIN_2);
}

bool drivers::get_button_pressed()
{
    int val = GPIOPinRead(GPIO_PORTL_BASE, GPIO_PIN_2);
    return !((bool)val);
}