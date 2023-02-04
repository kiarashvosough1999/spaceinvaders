/*
 * custom_character.c
 *
 *  Created on: Jan 27, 2023
 *      Author: kiarashvosough
 */

#include "custom_character.h"
#include "custom_character_byte_code.h"
#include <main.h>
#include "LiquidCrystal.h"

void register_custom_characters() {
	createChar(senior, senior_enemy_char);
    createChar(mid, mid_enemy_char);
    createChar(junior, junior_enemy_char);
    createChar(player_1, senior_enemy_char);
    createChar(player_shot, shot_char);
}

int get_custom_character_id(Custom_Character name) {
	switch (name) {
	case boss:
		return 1;
	case senior:
		return 2;
	case mid:
		return 3;
	case junior:
		return 4;
	case player_1:
		return 5;
	case player_shot:
		return 6;
	case enemy_shot:
		return 6;
	default:
		return -1;
	}
}

bool is_enemy_char(Custom_Character name) {
	return name == senior || name == mid || name == boss || name == junior ? true : false;
}

bool is_shot_char(Custom_Character name) {
	return name == player_shot || name == enemy_shot ? true : false;
}
