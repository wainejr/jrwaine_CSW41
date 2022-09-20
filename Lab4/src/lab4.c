#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#include "defines.h"
#include "setup.h"
#include "led.h"
#include "joystick.h"

int main()
{
  setupIOs();

  // activateLedRGB(100, 150, 200);
  // activateLedRGB(255, 255, 255);

  // deactivateLedRGB();

  
  while(1){
    int32_t val_hor = readJoystickHor();
    int32_t val_ver = readJoystickVer();
    int32_t val_sel = readJoystickSelect();

    UARTprintf("values hor %d ver %d sel %d\n", val_hor, val_ver, val_sel);
    break;
  }
  // readJoystickHor();
  // readJoystickVer();
  // readJoystickSelect();

  return 0;
}
