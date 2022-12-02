#include "GamePlay.h"

namespace models {

/**
*   @brief Types of ghost control
*   
*/
enum GhostControlType {
    CONTROL_RANDOM
};

/**
*   @brief Class with required informations to control a ghost
*   
*/
class GhostControl {
public:
    // Last ghost direction
    misc::Vector<int> last_dir;
    // Last ghost tile
    misc::Vector<int> last_tile;
    // Last tile where direction was updated
    misc::Vector<int> last_tile_dir_updated;
    // Ghost current tile
    misc::Vector<int> curr_tile;

    // Type of ghost control
    GhostControlType control_type;

    GamePlay* gameplay;
    Ghost* ghost;
    
    GhostControl(GhostControlType control_type, GamePlay* gameplay, Ghost* ghost);

    /**
    *   @brief Update ghost direction
    *   
    *   @param new_direction new direction to set to ghost
    */
    void update_direction(misc::Vector<int> new_direction);
};
}