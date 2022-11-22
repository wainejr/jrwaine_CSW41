/**
 *   @file Labyrinth.h
 *   @author Waine Jr. (waine@alunos.utfpr.edu.br)
 *   @brief Model for game labyrinth state and action management
 *   @version 0.1.0
 *   @date 21/11/2022
 *
 *   @copyright Copyright (c) 2022
 *
 */

#include "consts.h"

#ifndef _MODELS_LABYRINTH_H_
#define _MODELS_LABYRINTH_H_

namespace models {
class Labyrinth {

public:
    TilesTypes lab[31][28];
    Labyrinth();
};
} // namespace models
#endif