#include "GamePlay.h"

using namespace models;

bool is_tile_valid_for_agent(TilesTypes tl, bool is_ghost)
{
    if (tl == TilesTypes::WALL) {
        return false;
    }
    if (tl == TilesTypes::TUNNEL && !is_ghost) {
        return false;
    }
    return true;
}

GamePlay::GamePlay()
{
    this->pac = PacMan();

    this->ghosts[0] = Ghost(GhostColors::RED);
    this->ghosts[1] = Ghost(GhostColors::YELLOW);
    this->ghosts[2] = Ghost(GhostColors::BLUE);
    this->ghosts[3] = Ghost(GhostColors::PINK);

    Ghost* ghosts_ref[4] = { &this->ghosts[0], &this->ghosts[1], &this->ghosts[2], &this->ghosts[3] };

    this->lab = Labyrinth();

    this->score = Score();
    this->is_init = false;

    this->last_update_sec = misc::get_current_time();
    this->start_time = misc::get_current_time();
}

void GamePlay::correct_agent_position(Agent* a, bool is_ghost)
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
    bool is_valid = is_tile_valid_for_agent(tl, is_ghost);

    // Agent stopped, only round values if tile is not valid
    if (a->direction.x == 0 && a->direction.y == 0) {
        if (!is_valid) {
            a->pos.x = round(a->pos.x);
            a->pos.y = round(a->pos.y);
        }
        // Agent to x direction, round y always and x if tile is not valid
    } else if (a->direction.x != 0) {
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
    this->correct_agent_position(&this->pac, false);
    for (int i = 0; i < 4; i++) {
        this->ghosts[i].update_position(vel_factor);
        this->correct_agent_position(&this->ghosts[i], true);
    }
}

bool GamePlay::validate_direction_change(
    Agent* a,
    misc::Vector<float> direction,
    bool is_ghost)
{
    misc::Vector<int> curr_tile = a->get_agent_tile();
    misc::Vector<int> change_dir = misc::Vector<int>(direction.x, direction.y);
    curr_tile.add(change_dir);

    TilesTypes tl = this->lab.get_tile(curr_tile.x, curr_tile.y);
    return is_tile_valid_for_agent(tl, is_ghost);
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
}

void GamePlay::update_pacman_direction(misc::Vector<float> new_direction)
{
    if (this->validate_direction_change(&this->pac, new_direction, false)) {
        this->pac.direction = new_direction;
        // Round values for direction
        if (new_direction.x != 0) {
            this->pac.pos.y = round(this->pac.pos.y);
        } else {
            this->pac.pos.x = round(this->pac.pos.x);
        }
    }
}
UpdateStatus::myEnum GamePlay::update_gameplay_status()
{
    // Check collisions if pacman is normal
    if (this->pac.state == PacmanState::NORMAL) {
        for (int i = 0; i < 4; i++) {
            if (has_collision(&this->pac, &this->ghosts[i])) {
                return UpdateStatus::PACMAN_DIED;
            }
        }
    }
    if (this->lab.n_balls == 0) {
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