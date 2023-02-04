/*
 * custom_character.h
 *
 *  Created on: Jan 27, 2023
 *      Author: kiarashvosough
 */

#ifndef INC_CUSTOM_CHARACTER_H_
#define INC_CUSTOM_CHARACTER_H_

#include <bool.h>

typedef enum {
    boss = 1,
    senior,
    mid,
    junior,
	player_1,
	player_shot,
	enemy_shot,
	empty_char
} Custom_Character;

void register_custom_characters();

int get_custom_character_id(Custom_Character name);

bool is_enemy_char(Custom_Character name);

bool is_shot_char(Custom_Character name);

#endif /* INC_CUSTOM_CHARACTER_H_ */
