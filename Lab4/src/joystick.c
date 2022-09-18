#include "joystick.h"

int32_t readJoystickHor(){
    int32_t val = GPIOPinRead(GPIO_JOYSTICK_ANALOG_BASE, GPIO_JOYSTICK_HOR);
    return val;
}

int32_t readJoystickVer(){
    int32_t val = GPIOPinRead(GPIO_JOYSTICK_ANALOG_BASE, GPIO_JOYSTICK_VER);
    return val;
}

int32_t readJoystickSelect(){
    int32_t val = GPIOPinRead(GPIO_JOYSTICK_DIGITAL_BASE, GPIO_JOYSTICK_SEL);
    return val;
}
