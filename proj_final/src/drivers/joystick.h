/**
 *   @file joystick.h
 *   @author João Felipe Machado (jfsmachado98@gmail.com)
 *   @author Waine Jr. (waine@alunos.utfpr.edu.br)
 *   @brief Driver for interaction with BoosterPack's joystick
 *   @version 0.1.0
 *   @date 21/11/2022
 *
 *   @copyright Copyright (c) 2022
 *
 */

#include "driverlib/adc.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include <stdbool.h>
#include <stdint.h>

#include "../misc/Vector.h"

#ifndef _DRIVER_JOYSTICK_H_
#define _DRIVER_JOYSTICK_H_

namespace drivers {
void setup_joystick();

int get_joystick_x();
int get_joystick_y();

misc::Vector<int> get_joystick_pos();
}
#endif