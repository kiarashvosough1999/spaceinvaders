/*
 * game_configuration_state.h
 *
 *  Created on: Jan 11, 2023
 *      Author: kiarashvosough
 */

#ifndef INC_GAME_CONFIGURATION_STATE_H_
#define INC_GAME_CONFIGURATION_STATE_H_

#include "PageStuff/pages.h"
#include "bool.h"
#include "game_level.h"

typedef struct {
	int app_start_time;
	char player_name[10];
	bool is_player_name_set;
	Game_Level hardness_level;
	int player_points;

} Game_Configuration_State;

void init_game_configuration_state(Game_Configuration_State* state);

int app_startup_duration(Game_Configuration_State* state);

void set_player_name(Game_Configuration_State* state, char player_name[10]);

void get_player_name(Game_Configuration_State* state, char player_name[10]);

void set_hardness_level(Game_Configuration_State* state, Game_Level level);

void add_point_(Game_Configuration_State* state, int point);

#endif /* INC_GAME_CONFIGURATION_STATE_H_ */
