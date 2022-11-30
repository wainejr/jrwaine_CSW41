/**
 *   @file all.h
 *   @author João Felipe Machado (jfsmachado98@gmail.com)
 *   @author Waine Jr. (waine@alunos.utfpr.edu.br)
 *   @brief Setup of all drivers
 *   @version 0.1.0
 *   @date 21/11/2022
 *
 *   @copyright Copyright (c) 2022
 *
 */

#include "button.h"
#include "buzzer.h"
#include "joystick.h"
#include "LCD.h"

#ifndef _DRIVER_ALL_H_
#define _DRIVER_ALL_H_

namespace drivers {
    void setup_all(tContext* pContext);
}
#endif