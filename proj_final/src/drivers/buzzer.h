/**
 *   @file buzzer.h
 *   @author João Felipe Machado (jfsmachado98@gmail.com)
 *   @author Waine Jr. (waine@alunos.utfpr.edu.br)
 *   @brief Driver for interaction with BoosterPack's buzzer
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
#include "driverlib/pwm.h"
#include "driverlib/sysctl.h"
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"


#ifndef _DRIVER_BUZZER_H_
#define _DRIVER_BUZZER_H_

namespace drivers {
    void setup_buzzer();

    void update_buzzer_value(float width);
}
#endif