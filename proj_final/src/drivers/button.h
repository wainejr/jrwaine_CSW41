/**
 *   @file button.h
 *   @author João Felipe Machado (jfsmachado98@gmail.com)
 *   @author Waine Jr. (waine@alunos.utfpr.edu.br)
 *   @brief Driver for interaction with Tiva's button
 *   @version 0.1.0
 *   @date 21/11/2022
 *
 *   @copyright Copyright (c) 2022
 *
 */

#include <stdbool.h>
#include <stdint.h>

#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/interrupt.h"
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"

#ifndef _DRIVER_BUTTON_H_
#define _DRIVER_BUTTON_H_

namespace drivers {
void setup_button();
void setup_interruption();

bool get_button_pressed();

}
#endif