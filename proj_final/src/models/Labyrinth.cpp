#include "./Labyrinth.h"

models::Labyrinth::Labyrinth()
{
    for (int j = 0; j < 31; j++) {
        for (int i = 0; i < 28; i++) {
            this->lab[j][i] = consts::INITIAL_LABYRINTH_STATE[j][i];
        }
    }
}
