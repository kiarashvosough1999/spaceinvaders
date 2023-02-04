/*
 * game_logic.c
 *
 *  Created on: Jan 28, 2023
 *      Author: kiarashvosough
 */


#include <game_logic.h>
#include <stdlib.h>
#include <time.h>
#include "game_level.h"
#include <main.h>

static void shift_player_shot_up(Game_Logic* logic);
static void shift_enemy_shot_down(Game_Logic* logic);
static void shift_enemies_down(Game_Logic* logic);
static void enemy_should_shot(Game_Logic* logic, Game_Level level);
static void init_game_board_for(Board_Character** current_board, Game_Level level);

// initialization

void init_game_logic(Game_Logic* logic, Game_Level level) {

	Board_Character** current_board;
	int row_count = 20;
	int column_count = 4;
	// First allocate memory for `size` number of pointers
	// I.e. we allocate an "array" of pointers
	current_board = malloc(row_count * sizeof(Board_Character*));

	// Then allocate each entry in the above allocated "array"
	// I.e. make each pointer in the "array" point to an "array" of `int`
	for (int i = 0; i < row_count; ++i)
		current_board[i] = malloc(column_count * sizeof(Board_Character));
	init_game_board_for(current_board, level);

	Index_Path player_position = { 19, 0 };

	int enemies_movement_frequency = get_enemies_movement_freq(level);
	int enemies_rows_count = get_enemies_rows_count(level);
	int total_enemies_count = get_enemies_count(level);

	Game_Logic new_logic = {
			player_position,
			0, // last_time_enemies_moved
			enemies_movement_frequency,
			0, // enemies_start_row_index
			enemies_rows_count,
			total_enemies_count, // enemies left
			NULL,
			NULL,
			NULL,
			NULL,
			NULL,
			current_board // current_board
	};

	*logic = new_logic;
}

void user_should_move(Game_Logic* logic, Direction direction) {

	int column = logic->player_position.column;

	if (direction == left) {
		column -= 1;
		if (column < 0) {
			column = 3;
		}
	} else if (direction == right) {
		column += 1;
		if (column > 3) {
			column = 0;
		}
	} else {
		return;
	}

	Index_Path player_position = { 19, column, direction };

	// last position on board
	Board_Character last_player_element = logic->current_board[logic->player_position.row][logic->player_position.column];

	// new position on board
	logic->current_board[player_position.row][player_position.column] = last_player_element;

	// clean last position
	change_board_char_to_none(&logic->current_board[logic->player_position.row][logic->player_position.column]);
	logic->player_position = player_position;
}

void user_did_shot(Game_Logic* logic, Game_Level level) {
	Board_Character shot;
	init_board_character(&shot, player_shot, level);

	logic->current_board[logic->player_position.row - 1][logic->player_position.column] = shot;
}


void time_did_passed(Game_Logic* logic, int current_time, Game_Level level) {

	// check if we need to move enemies down
	int duration_passed = current_time - logic->last_time_enemies_moved;
	if (duration_passed >= logic->enemies_movement_frequency) {
		shift_enemies_down(logic);

		logic->last_time_enemies_moved = current_time;
	}

	// update shots
	shift_enemy_shot_down(logic);
	shift_player_shot_up(logic);
	enemy_should_shot(logic, level);
}

// private APIs

static void init_game_board_for(Board_Character** current_board, Game_Level level) {

	// first initialize each element to empty state.
	for (int i = 0; i < 20; i ++) {
		for (int j = 0; j < 4; j++) {
			Board_Character empty;
			init_board_character(&empty, empty_char, level);
			current_board[i][j] = empty;
		}
	}

	int sens = get_senior_enemies_count(level) / 4;
	sens = sens == 0 ? 1 : sens; // for zero values

	for (int i = 0; i < sens; i ++) {
		for (int j = 0; j < 4; j++) { // count will never be more than 4
			Board_Character senior_enemy;
			init_board_character(&senior_enemy, senior, level);
			current_board[i][j] = senior_enemy;
		}
	}

	int mids = get_mid_enemies_count(level)/4;
	mids = mids == 0 ? 1 : mids; // for zero values
	mids += sens;
	for (int i = sens; i < mids; i ++) {
		for (int j = 0; j < 4; j++) { // count will never be more than 4
			Board_Character mid_enemy;
			init_board_character(&mid_enemy, mid, level);
			current_board[i][j] = mid_enemy;
		}
	}

	int juniors = get_junior_enemies_count(level) / 4;
	juniors = juniors == 0 ? 1 : juniors; // for zero values
	juniors += mids;

	for (int i = mids; i < juniors; i ++) {
		for (int j = 0; j < 4; j++) { // count will never be mor than 4
			Board_Character junior_enemy;
			init_board_character(&junior_enemy, junior, level);
			current_board[i][j] = junior_enemy;
		}
	}

	// place player at the end of screen.
	Board_Character player;
	init_board_character(&player, player_1, level);
	current_board[19][0] = player;
}

static void enemy_should_shot(Game_Logic* logic, Game_Level level) {

	if (random_bool() == false) { return; }

	int random_column = rand() % 4;

	int enemies_last_row_index = logic->enemies_start_row_index + logic->enemies_rows_count;

	Board_Character shot;
	init_board_character(&shot, enemy_shot, level);

	logic->current_board[enemies_last_row_index][random_column] = shot;
}

static void handle_player_got_shot(Game_Logic* logic, Board_Character* player) {
	int lives = player->lives;
	if (lives > 0) {
		player->lives--;
	}

	if (player->lives == 1) {
		logic->player_is_about_to_die();
	}

	// game over
	if (player->lives == 0) {
		// enemy was destroyed by shot
		change_board_char_to_none(player);
		logic->enemies_did_win();
		// set point for death
	}
}

static void handle_enemy_got_shot(Game_Logic* logic, Board_Character* enemy) {
	int lives = enemy->lives;
	if (lives > 0) {
		enemy->lives -= 1;
		// set point for shot
		logic->enemies_got_shot(10);
	}

	if (enemy->lives == 0) {
		logic->enemies_left -= 1;
		// enemy was destroyed by shot
		change_board_char_to_none(enemy);
		logic->enemies_got_shot(20);
		// set point for death
	}

	if(logic->enemies_left == 0) {
		logic->player_did_win();
	}
}

static void shift_enemies_down(Game_Logic* logic) {

	int enemies_last_row_index = logic->enemies_start_row_index + logic->enemies_rows_count;

	if (enemies_last_row_index >= 19) { return; }

	// shift down from bottom
	for(int row = enemies_last_row_index; row >= logic->enemies_start_row_index; row--){
		for (int col = 0; col < 4; col++) { //

			if (is_enemy_char(logic->current_board[row][col].type) == true) {
				logic->current_board[row + 1][col] = logic->current_board[row][col];
			}

			if (row == logic->enemies_start_row_index) {
				// in order to not display it on screen,
				// although it has value
				// but is not valid.
				change_board_char_to_none(&logic->current_board[row][col]);
			}
		}
	}
	// increment start position by one
	logic->enemies_start_row_index += 1;
}

// shot moving

static void shift_player_shot_up(Game_Logic* logic) {

	int enemies_last_row_index = logic->enemies_start_row_index + logic->enemies_rows_count;

	// check if any impact happened after shifting up
	for (int row = enemies_last_row_index; row < 19; row++) {
		for (int col = 0; col < 4; col++) {
			Board_Character element = logic->current_board[row][col];

			// check if we have player shot
			if(element.is_empty == false && element.type == player_shot) {

				// check if an enemy is placed at the top of shot
				if (logic->current_board[row - 1][col].is_empty == false &&
						is_enemy_char(logic->current_board[row - 1][col].type) == true
				) {
					handle_enemy_got_shot(logic, &logic->current_board[row - 1][col]);
				}
				// check if an enemy's shot is placed at the top of shot
				else if(
						logic->current_board[row - 1][col].is_empty == false &&
						logic->current_board[row - 1][col].type == enemy_shot
				) {
					// remove enemy shot
					change_board_char_to_none(&logic->current_board[row - 1][col]);
				}
				else if (row - 1 < 0) {
					// do nothing as the shot will go out of screen
				} else {
					// if top is empty, shift shot up.
					logic->current_board[row - 1][col] = logic->current_board[row][col];
				}
				change_board_char_to_none(&logic->current_board[row][col]);
			}
		}
	}
}

static void shift_enemy_shot_down(Game_Logic* logic) {
	int enemies_last_row_index = logic->enemies_start_row_index + logic->enemies_rows_count;

	// check if any impact happened after shifting down
	for (int row = 19; row >= enemies_last_row_index; row--) {
		for (int col = 0; col < 4; col++) {
			Board_Character element = logic->current_board[row][col];

			// check if we have enemy shot
			if(element.is_empty == false && element.type == enemy_shot) {

				// check if an player is placed at the bottom of shot
				if (logic->current_board[row + 1][col].is_empty == false &&
						logic->current_board[row + 1][col].type == player_1
				) {
					handle_player_got_shot(logic, &logic->current_board[row - 1][col]);
				}
				// check if an player's shot is placed at the bottom of shot
				else if(
						logic->current_board[row + 1][col].is_empty == false &&
						logic->current_board[row + 1][col].type == player_shot
				) {
					// remove player shot
					change_board_char_to_none(&logic->current_board[row + 1][col]);
				}
				else if (row + 1 > 19) {
					// do nothing as the shot will go out of screen
				} else {
					// if bottom is empty, shift shot down.
					logic->current_board[row + 1][col] = logic->current_board[row][col];
				}
				change_board_char_to_none(&logic->current_board[row][col]);
			}
		}
	}
}
