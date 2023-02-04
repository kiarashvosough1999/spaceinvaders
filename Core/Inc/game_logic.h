/*
 * game_logic.h
 *
 *  Created on: Jan 28, 2023
 *      Author: kiarashvosough
 */

#ifndef INC_GAME_LOGIC_H_
#define INC_GAME_LOGIC_H_

#include <bool.h>
#include <board_characters.h>
#include <game_level.h>
#include <Index_Path.h>

typedef struct {
	Index_Path player_position;
	int last_time_enemies_moved;
	int enemies_movement_frequency;
	int enemies_start_row_index;
	int enemies_rows_count;
	int enemies_left;
	void (*player_is_about_to_die)(void);
	void (*there_is_only_3_enemies_left)(void);
	void (*player_did_win)(void);
	void (*enemies_did_win)(void);
	void (*enemies_got_shot)(int);
	Board_Character** current_board;
} Game_Logic;

void init_game_logic(Game_Logic* logic, Game_Level level);

void time_did_passed(Game_Logic* logic, int current_time, Game_Level level);

void user_should_move(Game_Logic* logic, Direction direction);

void user_did_shot(Game_Logic* logic, Game_Level level);

#endif /* INC_GAME_LOGIC_H_ */
