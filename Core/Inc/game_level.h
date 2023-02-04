/*
 * game_level.h
 *
 *  Created on: Jan 21, 2023
 *      Author: kiarashvosough
 */

#ifndef INC_GAME_LEVEL_H_
#define INC_GAME_LEVEL_H_

#include <custom_character.h>

typedef enum {
	easy,
	normal,
	hard
} Game_Level;

int get_enemies_movement_freq(Game_Level level);

int get_enemies_rows_count(Game_Level level);

int get_enemies_count(Game_Level level);

int get_senior_enemies_count(Game_Level level);

int get_mid_enemies_count(Game_Level level);

int get_junior_enemies_count(Game_Level level);

int get_character_lives(Custom_Character name, Game_Level level);
#endif /* INC_GAME_LEVEL_H_ */
