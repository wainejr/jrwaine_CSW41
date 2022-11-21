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

namespace models {
enum TilesTypes { WALL,
    TUNNEL,
    PATH,
    SMALL_BALL,
    SUPER_BALL };

class Labyrinth {

public:
    TilesTypes lab[31][28];
    Labyrinth();
};
} // namespace models
