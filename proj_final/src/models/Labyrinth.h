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

#include "Ghost.h"
#include "PacMan.h"
#include "consts.h"

#ifndef _MODELS_LABYRINTH_H_
#define _MODELS_LABYRINTH_H_

namespace models {

/**
*   @brief Labyrinth representation
*   
*/
class Labyrinth {

public:
    // Labyrinth tiles
    TilesTypes lab[consts::MAZE_SIZE_Y][consts::MAZE_SIZE_X];
    // Number of balls in labyrinth currently
    int n_balls;

    Labyrinth();

    /**
    *   @brief Get tile in given position
    *   
    *   @param x position in x
    *   @param y position in y
    *   @return TilesTypes tile in given position
    */
    TilesTypes get_tile(int x, int y);
    /**
    *   @brief Consume ball in given tile
    *   
    *   @param x position in x
    *   @param y position in y
    */
    void consume_tile(int x, int y);

    /**
    *   @brief Check if tile is inside cave
    *   
    *   @param x position in x
    *   @param y position in y
    *   @return true it is inside cave
    *   @return false it is not inside cave
    */
    bool is_incave(int x, int y);
};
} // namespace models
#endif