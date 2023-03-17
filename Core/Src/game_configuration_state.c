/*
 * game_configuration_state.c
 *
 *  Created on: Jan 11, 2023
 *      Author: kiarashvosough
 */

#include "game_configuration_state.h"
#include "PageStuff/pages.h"
#include "main.h"
#include "string.h"

void init_game_configuration_state(Game_Configuration_State* state) {
	Game_Configuration_State new_state = {
			HAL_GetTick(),
			"",
			false,
			easy,
			0,
			false
	};
	*state = new_state;
}

int app_startup_duration(Game_Configuration_State* state) {
	return HAL_GetTick() - state->app_start_time;
}

void get_player_name(Game_Configuration_State* state, char player_name[10]) {
	if (state->is_player_name_set == true) {
		strcpy(player_name, state->player_name);
	}
}

void set_player_name(Game_Configuration_State* state, char player_name[10]) {
	strcpy(state->player_name, player_name);
	state->is_player_name_set = true;
}

void set_hardness_level(Game_Configuration_State* state, Game_Level level) {
	state->hardness_level = level;
}

void add_point_(Game_Configuration_State* state, int point) {
	state->player_points += point;
}

void set_is_playing(Game_Configuration_State* state, bool is_playing) {
	state->is_playing = is_playing;
}

bool get_is_playing(Game_Configuration_State* state) {
	return state->is_playing;
}





