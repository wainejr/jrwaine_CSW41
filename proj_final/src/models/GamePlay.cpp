#include "GamePlay.h"

using namespace models;

bool is_tile_valid_for_agent(TilesTypes tl, bool tunnel_allowed)
{
    if (tl == TilesTypes::WALL) {
        return false;
    }
    if (tl == TilesTypes::TUNNEL && !tunnel_allowed) {
        return false;
    }
    return true;
}

GamePlay::GamePlay()
{
    this->pac = PacMan();

    this->ghosts[0] = Ghost(GhostColors::RED);
    this->ghosts[1] = Ghost(GhostColors::ORANGE);
    this->ghosts[2] = Ghost(GhostColors::BLUE);
    this->ghosts[3] = Ghost(GhostColors::PINK);

    Ghost* ghosts_ref[4] = { &this->ghosts[0], &this->ghosts[1], &this->ghosts[2], &this->ghosts[3] };

    this->lab = Labyrinth();
    this->gamestate = GAME_STATE_RUNNING;

    this->score = Score();
    this->is_init = false;

    this->last_update_sec = misc::get_current_time();
    this->start_time = misc::get_current_time();
}

void GamePlay::correct_agent_position(Agent* a, bool tunnel_allowed, bool correct_perpendicular)
{
    misc::Vector<int> tile_to_check = misc::Vector<int>(a->pos.x, a->pos.y);
    // Top-left corner is reference for negative velocities
    // Botom-right corner is reference for positive velocities
    if (a->direction.y == 1) {
        tile_to_check.y += 1;
    } else if (a->direction.x == 1) {
        tile_to_check.x += 1;
    }
    TilesTypes tl = this->lab.get_tile(tile_to_check.x, tile_to_check.y);
    bool is_valid = is_tile_valid_for_agent(tl, tunnel_allowed);

    // Agent stopped, only round values if tile is not valid
    if (a->direction.x == 0 && a->direction.y == 0) {
        if (!is_valid) {
            a->pos.x = round(a->pos.x);
            a->pos.y = round(a->pos.y);
        }
        // Agent to x direction, round y always and x if tile is not valid
    } else if (a->direction.x != 0) {
        if (correct_perpendicular)
            a->pos.y = round(a->pos.y);
        if (!is_valid) {
            // Passed to the right
            if (a->direction.x == 1)
                a->pos.x = floor(a->pos.x);
            // Passed to the left
            else
                a->pos.x = ceil(a->pos.x);
        }
        // Agent to y direction, round x always and y if tile is not valid
    } else if (a->direction.y != 0) {
        if (correct_perpendicular)
            a->pos.x = round(a->pos.x);
        if (!is_valid) {
            // Passed to the bottom
            if (a->direction.y == 1)
                a->pos.y = floor(a->pos.y);
            // Passed to the top
            else
                a->pos.y = ceil(a->pos.y);
        }
    }
    // Invalid tile for agent, stop agent
    if (!is_valid) {
        a->direction.x = 0;
        a->direction.y = 0;
    }
};

void GamePlay::update_positions(float vel_factor)
{
    this->pac.update_position(vel_factor);
    this->correct_agent_position(&this->pac, false, true);
    for (int i = 0; i < 4; i++) {
        this->ghosts[i].update_position(vel_factor);
        // Ghosts locked in cave are not allowed to pass tunnel
        bool tunnel_allowed = this->ghosts[i].state != GhostState::LOCKED_CAVE;
        // Don't correct perpendicular position for ghosts locked in cave or going out of it
        bool correct_perpendicular = this->ghosts[i].state != GhostState::LOCKED_CAVE;
        this->correct_agent_position(&this->ghosts[i], tunnel_allowed, correct_perpendicular);
    }
}

bool GamePlay::validate_direction_change(
    Agent* a,
    misc::Vector<float> direction,
    bool tunnel_allowed)
{
    misc::Vector<int> curr_tile = a->get_agent_tile();
    misc::Vector<int> change_dir = misc::Vector<int>(direction.x, direction.y);
    curr_tile.add(change_dir);

    TilesTypes tl = this->lab.get_tile(curr_tile.x, curr_tile.y);
    return is_tile_valid_for_agent(tl, tunnel_allowed);
}

bool GamePlay::has_collision(PacMan* pac, Ghost* ghost)
{
    misc::Vector<int> tile_pac = pac->get_agent_tile();
    misc::Vector<int> tile_ghost = ghost->get_agent_tile();
    return tile_pac.x == tile_ghost.x && tile_pac.y == tile_ghost.y;
}

void GamePlay::update_labyrinth_score()
{
    misc::Vector<int> tile_pac = this->pac.get_agent_tile();
    TilesTypes tl = this->lab.get_tile(tile_pac.x, tile_pac.y);

    // Consume and process ball
    if (tl == TilesTypes::SMALL_BALL) {
        this->score.curr_score += this->score.multiplier * consts::SMALL_BALL_SCORE;
        this->lab.consume_tile(tile_pac.x, tile_pac.y);

    } else if (tl == TilesTypes::SUPER_BALL) {
        this->score.curr_score += this->score.multiplier * consts::SUPER_BALL_SCORE;
        this->lab.consume_tile(tile_pac.x, tile_pac.y);
        this->pac.into_super();
        this->ghosts[0].into_afraid();
        this->ghosts[1].into_afraid();
        this->ghosts[2].into_afraid();
        this->ghosts[3].into_afraid();
    }

    // Update score multiplier
    if (this->score.multiplier <= consts::SCORE_MIN_MUL) {
        this->score.multiplier = consts::SCORE_MIN_MUL;
    } else {
        this->score.multiplier -= consts::SCORE_MUL_DECREASE_PER_UPDATE;
    }
}

void GamePlay::update_pacman_state()
{
    this->pac.tick_update();
}

void GamePlay::update_ghost_state(Ghost* ghost)
{
    misc::Vector<int> ghost_tile = ghost->get_agent_tile();
    ghost->tick_update();

    switch (ghost->state) {
    case GhostState::AFRAID:
        if (pac.state != PacmanState::SUPER) {
            ghost->into_walking();
        }
        break;
    case GhostState::IN_CAVE:
        if (pac.state == PacmanState::NORMAL) {
            if (this->lab.is_incave(ghost_tile.x, ghost_tile.y)) {
                ghost->into_outcave();
            } else {
                ghost->into_walking();
            }
        } else {
            if (ghost_tile.x == consts::GHOST_RESET_INCAVE_POSITION[0]
                && ghost_tile.y == consts::GHOST_RESET_INCAVE_POSITION[1]) {
                ghost->into_outcave();
            }
        }
        break;
    case GhostState::OUT_CAVE:
        if (!this->lab.is_incave(ghost_tile.x, ghost_tile.y)) {
            ghost->into_walking();
        }
        break;
    case GhostState::LOCKED_CAVE:
        if (ghost->is_free_from_cave_lock()) {
            ghost->into_outcave();
        }
        break;
    default:
        break;
    }
}

void GamePlay::update_agent_direction(Agent* agent, misc::Vector<float> new_direction, bool tunnel_allowed)
{
    // No update needed
    if (new_direction.x == agent->direction.x && new_direction.y == agent->direction.y) {
        return;
    }
    if (this->validate_direction_change(agent, new_direction, tunnel_allowed)) {
        agent->direction = new_direction;
        // Round values for direction
        if (new_direction.x != 0) {
            agent->pos.y = round(agent->pos.y);
        } else if (new_direction.y != 0) {
            agent->pos.x = round(agent->pos.x);
        }
    }
}

void GamePlay::update_pacman_direction(misc::Vector<float> new_direction)
{
    this->update_agent_direction(&this->pac, new_direction, false);
}

void GamePlay::update_ghost_direction(Ghost* ghost, misc::Vector<float> new_direction)
{
    this->update_agent_direction(ghost, new_direction, true);
}

UpdateStatus::myEnum GamePlay::update_gameplay_status()
{
    // Check collisions
    for (int i = 0; i < 4; i++) {
        bool has_coll = has_collision(&this->pac, &this->ghosts[i]);
        if (!has_coll)
            continue;
        // In case of collision, check ghost state
        switch (this->ghosts[i].state) {
        case GhostState::AFRAID:
            this->ghosts[i].into_incave();
            this->score.curr_score += consts::GHOST_AFRAID_SCORE * this->score.multiplier;
            break;
        case GhostState::IN_CAVE:
            // Nothing happens, pacman is super and ghost is back to cave
            break;
        case GhostState::WALKING:
            this->gamestate = GameState::GAME_STATE_ENDED;
            return UpdateStatus::PACMAN_DIED;
        case GhostState::OUT_CAVE:
            this->gamestate = GameState::GAME_STATE_ENDED;
            return UpdateStatus::PACMAN_DIED;
        default:
            break;
        }
    }

    if (this->lab.n_balls == 0) {
        this->gamestate = GameState::GAME_STATE_ENDED;
        return UpdateStatus::GAME_FINISHED;
    }
    return UpdateStatus::GAME_CONTINUE;
}

UpdateStatus::myEnum GamePlay::update()
{
    float vel_factor;
    vel_factor = consts::STATE_UPDATE_SEC_INTERVAL;

    this->update_positions(vel_factor);
    this->update_pacman_state();
    this->update_ghost_state(&this->ghosts[0]);
    this->update_ghost_state(&this->ghosts[1]);
    this->update_ghost_state(&this->ghosts[2]);
    this->update_ghost_state(&this->ghosts[3]);
    this->update_labyrinth_score();

    return this->update_gameplay_status();
}