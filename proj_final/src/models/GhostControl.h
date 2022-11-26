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

    misc::Vector<int> last_dir;
    misc::Vector<int> last_tile;
    misc::Vector<int> last_tile_dir_updated;
    misc::Vector<int> curr_tile;

    GhostControlType control_type;

    GamePlay* gameplay;
    Ghost* ghost;

    GhostControl(GhostControlType control_type, GamePlay* gameplay, Ghost* ghost);

    void update();
    void update_path();

    void update_direction(misc::Vector<int> new_direction);
};
}