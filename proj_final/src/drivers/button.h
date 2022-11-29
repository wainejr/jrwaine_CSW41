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

#ifndef _DRIVER_BUTTON_H_
#define _DRIVER_BUTTON_H_

namespace drivers {
    void setup_button();

    bool get_button_pressed();
}
#endif