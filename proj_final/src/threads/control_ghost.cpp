#include "control_ghost.h"

bool is_direction_possible(models::GhostControl* ghost_control, misc::Vector<int> direction, bool tunnel_allowed)
{
    misc::Vector<int> tile_check = ghost_control->ghost->get_agent_tile();
    // Add direction
    tile_check.add(direction);
    models::TilesTypes tl = ghost_control->gameplay->lab.get_tile(tile_check.x, tile_check.y);
    if (tl == models::TilesTypes::WALL) {
        return false;
    }
    if (tl == models::TilesTypes::TUNNEL && !tunnel_allowed) {
        return false;
    }
    return true;
}

int get_possible_directions(models::GhostControl* ghost_control, misc::Vector<int> possible_directions[], bool tunnel_allowed)
{
    int all_directions[4][2] = { { 0, 1 }, { 0, -1 }, { 1, 0 }, { -1, 0 } };
    int n_possible_dirs = 0;
    for (int i = 0; i < 4; i++) {
        misc::Vector<int> direction = misc::Vector<int>(all_directions[i]);
        if (is_direction_possible(ghost_control, direction, tunnel_allowed)) {
            possible_directions[n_possible_dirs] = direction;
            n_possible_dirs += 1;
        }
    }
    return n_possible_dirs;
}

void update_ghost_tile(models::GhostControl* ghost_control)
{
    misc::Vector<int> curr_tile = ghost_control->ghost->get_agent_tile();
    if (curr_tile.x != ghost_control->curr_tile.x || curr_tile.y != ghost_control->curr_tile.y) {
        ghost_control->last_tile = ghost_control->curr_tile;
        ghost_control->curr_tile = curr_tile;
    }
}

void control_incave(models::GhostControl* ghost_control)
{
}

void control_outcave(models::GhostControl* ghost_control)
{
    misc::Vector<int> direction(0, 0);
    if (ghost_control->curr_tile.x < models::consts::LAB_LEFT_TUNNEL[0]) {
        direction.x = 1;
        direction.y = 0;
    } else if (ghost_control->curr_tile.x > models::consts::LAB_RIGHT_TUNNEL[0]) {
        direction.x = -1;
        direction.y = 0;
    } else {
        direction.x = 0;
        direction.y = -1;
    }
    ghost_control->update_direction(direction);
}

void set_random_direction(models::GhostControl* ghost_control, misc::Vector<int> dir_exclude)
{
    misc::Vector<int> possible_dirs[4];
    misc::Vector<int> last_dir = ghost_control->last_dir;
    int n_possible_dirs = get_possible_directions(ghost_control, possible_dirs, false);
    int idx = rand() % n_possible_dirs;

    misc::Vector<int> dir_use = possible_dirs[idx];
    if (dir_use.x == dir_exclude.x && dir_use.y == dir_exclude.y) {
        int new_idx = (idx + 1) % n_possible_dirs;
        if (new_idx == idx)
            return;
        dir_use = possible_dirs[new_idx];
    }
    ghost_control->update_direction(dir_use);
}

bool is_ghost_in_crossing(models::GhostControl* ghost_control)
{
    misc::Vector<int> possible_dirs[4];
    misc::Vector<float> ghost_dir_float = ghost_control->ghost->direction;

    int n_possible_dirs = get_possible_directions(ghost_control, possible_dirs, false);
    for (int i = 0; i < n_possible_dirs; i++) {
        misc::Vector<int> dir = possible_dirs[i];
        // Moving in x direction
        if (ghost_dir_float.x != 0) {
            // Possible to move in y
            if (dir.y != 0) {
                return true;
            }
        }
        // Moving in y direction
        else if (ghost_dir_float.y != 0) {
            // Possible to move in x
            if (dir.x != 0) {
                return true;
            }
        }
    }
    return false;
}

void control_walking(models::GhostControl* ghost_control)
{
    models::Ghost* ghost = ghost_control->ghost;
    bool is_in_updated_tile = ghost_control->curr_tile.x == ghost_control->last_tile_dir_updated.x && ghost_control->curr_tile.y == ghost_control->last_tile_dir_updated.y;
    if (ghost->direction.x == 0 && ghost->direction.y == 0) {
        set_random_direction(ghost_control, ghost_control->last_dir);
    } else if (is_ghost_in_crossing(ghost_control)) {
        // Check if is in tile where velocity was updated
        if (!is_in_updated_tile) {
            // Ghost does not "turn back" in crossing section
            misc::Vector<int> opposite_dir = ghost_control->last_dir.mul(-1);
            set_random_direction(ghost_control, opposite_dir);
        }
    }
}

void control_afraid(models::GhostControl* ghost_control)
{
    // Same as walking, because walking is random
    control_walking(ghost_control);
}

void control_locked_cave(models::GhostControl* ghost_control)
{
    models::Ghost* ghost = ghost_control->ghost;
    // Ghost walking up and down
    if (ghost->direction.x == 0 && ghost->direction.y == 0) {
        misc::Vector<int> new_dir = misc::Vector<int>(0, 0);
        // Current y is greater than where direction was last updated
        if (ghost_control->last_tile_dir_updated.y < ghost_control->curr_tile.y) {
            new_dir.y = -1;
        } else {
            new_dir.y = 1;
        }
        ghost_control->update_direction(new_dir);
    }
}

#if USE_SFML
void control_ghost_loop(models::GamePlay* gameplay, models::Ghost* ghost, int random_seed)
{  
  // Initialize random seed
    srand(random_seed);
    models::GhostControl ghost_control(models::CONTROL_RANDOM, gameplay, ghost);

    while (gameplay->gamestate == models::GAME_STATE_RUNNING) {
        update_ghost_tile(&ghost_control);
        switch (ghost->state) {
        case models::GhostState::IN_CAVE:
            control_incave(&ghost_control);
            break;
        case models::GhostState::OUT_CAVE:
            control_outcave(&ghost_control);
            break;
        case models::GhostState::WALKING:
            control_walking(&ghost_control);
            break;
        case models::GhostState::AFRAID:
            control_afraid(&ghost_control);
            break;
        case models::GhostState::LOCKED_CAVE:
            control_locked_cave(&ghost_control);
            break;
        default:
            break;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(
            (int)(1000 * models::consts::STATE_UPDATE_SEC_INTERVAL)));
    }
}
#else
void control_ghost_loop(ULONG ghost_idx)
{
    models::GamePlay* gameplay = &g_game.gameplay;
    models::Ghost* ghost = &gameplay->ghosts[ghost_idx];

    // Initialize random seed
    models::GhostControl ghost_control(models::CONTROL_RANDOM, gameplay, ghost);

    while(true){
      srand(ghost_idx*50+tx_time_get());
      while (gameplay->gamestate == models::GAME_STATE_RUNNING) {
          update_ghost_tile(&ghost_control);
          switch (ghost->state) {
          case models::GhostState::IN_CAVE:
              control_incave(&ghost_control);
              break;
          case models::GhostState::OUT_CAVE:
              control_outcave(&ghost_control);
              break;
          case models::GhostState::WALKING:
              control_walking(&ghost_control);
              break;
          case models::GhostState::AFRAID:
              control_afraid(&ghost_control);
              break;
          case models::GhostState::LOCKED_CAVE:
              control_locked_cave(&ghost_control);
              break;
          default:
              break;
          }
          
            tx_thread_sleep(THREAD_GHOST_PERIOD);
      }
      tx_thread_suspend(&g_thread_ghosts[ghost_idx]);
    }
}


void    initialize_threads_control_ghosts(){
    /* Memory pointer */
    CHAR *pointer = (CHAR*)TX_NULL;

    for(int i = 0; i < 4; i++){
        /* Allocate the stack for display thread  */
        tx_byte_allocate(&g_byte_pool, (VOID **) &pointer, STACK_SIZE, TX_NO_WAIT);
        /* Create the thread for display  */
        tx_thread_create(&g_thread_ghosts[i], "thread ghost", control_ghost_loop, i, pointer, 
            STACK_SIZE, 0, 0, 1, TX_AUTO_START);
    }
}

#endif