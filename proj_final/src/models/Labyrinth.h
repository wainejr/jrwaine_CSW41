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

const TilesTypes INITIAL_LABYRINTH_STATE[31][28] = {
    { W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W },
    { W, s, s, s, s, s, s, s, s, s, s, s, s, W, W, s, s, s, s, s, s, s, s, s, s, s, s, W },
    { W, s, W, W, W, W, s, W, W, W, W, W, s, W, W, s, W, W, W, W, W, s, W, W, W, W, s, W },
    { W, S, W, W, W, W, s, W, W, W, W, W, s, W, W, s, W, W, W, W, W, s, W, W, W, W, S, W },
    { W, s, W, W, W, W, s, W, W, W, W, W, s, W, W, s, W, W, W, W, W, s, W, W, W, W, s, W },
    { W, s, s, s, s, s, s, s, s, s, s, s, s, s, s, s, s, s, s, s, s, s, s, s, s, s, s, W },
    { W, s, W, W, W, W, s, W, W, s, W, W, W, W, W, W, W, W, s, W, W, s, W, W, W, W, s, W },
    { W, s, W, W, W, W, s, W, W, s, W, W, W, W, W, W, W, W, s, W, W, s, W, W, W, W, s, W },
    { W, s, s, s, s, s, s, W, W, s, s, s, s, W, W, s, s, s, s, W, W, s, s, s, s, s, s, W },
    { W, W, W, W, W, W, s, W, W, W, W, W, p, W, W, p, W, W, W, W, W, s, W, W, W, W, W, W },
    { W, W, W, W, W, W, s, W, W, W, W, W, p, W, W, p, W, W, W, W, W, s, W, W, W, W, W, W },
    { W, W, W, W, W, W, s, W, W, p, p, p, p, p, p, p, p, p, p, W, W, s, W, W, W, W, W, W },
    { W, W, W, W, W, W, s, W, W, p, W, W, W, T, T, W, W, W, p, W, W, s, W, W, W, W, W, W },
    { W, W, W, W, W, W, s, W, W, p, W, p, p, p, p, p, p, W, p, W, W, s, W, W, W, W, W, W },
    { p, p, p, p, p, p, s, p, p, p, W, p, p, p, p, p, p, W, p, p, p, s, p, p, p, p, p, p },
    { W, W, W, W, W, W, s, W, W, p, W, p, p, p, p, p, p, W, p, W, W, s, W, W, W, W, W, W },
    { W, W, W, W, W, W, s, W, W, p, W, W, W, W, W, W, W, W, p, W, W, s, W, W, W, W, W, W },
    { W, W, W, W, W, W, s, W, W, p, p, p, p, p, p, p, p, p, p, W, W, s, W, W, W, W, W, W },
    { W, W, W, W, W, W, s, W, W, p, W, W, W, W, W, W, W, W, p, W, W, s, W, W, W, W, W, W },
    { W, W, W, W, W, W, s, W, W, p, W, W, W, W, W, W, W, W, p, W, W, s, W, W, W, W, W, W },
    { W, s, s, s, s, s, s, s, s, s, s, s, s, W, W, s, s, s, s, s, s, s, s, s, s, s, s, W },
    { W, s, W, W, W, W, s, W, W, W, W, W, s, W, W, s, W, W, W, W, W, s, W, W, W, W, s, W },
    { W, s, W, W, W, W, s, W, W, W, W, W, s, W, W, s, W, W, W, W, W, s, W, W, W, W, s, W },
    { W, S, s, s, W, W, s, s, s, s, s, s, s, p, p, s, s, s, s, s, s, s, W, W, s, s, S, W },
    { W, W, W, s, W, W, s, W, W, s, W, W, W, W, W, W, W, W, s, W, W, s, W, W, s, W, W, W },
    { W, W, W, s, W, W, s, W, W, s, W, W, W, W, W, W, W, W, s, W, W, s, W, W, s, W, W, W },
    { W, s, s, s, s, s, s, W, W, s, s, s, s, W, W, s, s, s, s, W, W, s, s, s, s, s, s, W },
    { W, s, W, W, W, W, W, W, W, W, W, W, s, W, W, s, W, W, W, W, W, W, W, W, W, W, s, W },
    { W, s, W, W, W, W, W, W, W, W, W, W, s, W, W, s, W, W, W, W, W, W, W, W, W, W, s, W },
    { W, s, s, s, s, s, s, s, s, s, s, s, s, W, W, s, s, s, s, s, s, s, s, s, s, s, s, W },
    { W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W },
};

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
