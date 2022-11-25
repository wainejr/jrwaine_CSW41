#include "GamePlay.h"

namespace models {

enum GhostControlType {
    CONTROL_RANDOM
};

class GhostControl {
public:
    misc::Vector<int> path_follow[100];
    int curr_path_pos;
    int path_size;

    misc::Vector<float> last_dir;
    misc::Vector<int> last_tile;

    GhostControlType control_type;

    GamePlay* gameplay;
    Ghost* ghost;

    GhostControl(GhostControlType control_type, GamePlay* gameplay, Ghost* ghost);

    void update();
    void update_path();
};
}