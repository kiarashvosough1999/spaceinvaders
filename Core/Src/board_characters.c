/*
 * board_characters.c
 *
 *  Created on: Jan 28, 2023
 *      Author: kiarashvosough
 */


#include "board_characters.h"

void init_board_character(Board_Character* bchar, Custom_Character type, Game_Level level) {
	Board_Character new_bchar = {
			type,
			get_custom_character_id(type),
			get_character_lives(type, level),
			type == empty_char ? true : false // is empty
	};

	*bchar = new_bchar;
}

int decrement_1_board_char_lives(Board_Character* bchar) {
	int decremented = bchar->lives - 1;
	// check if now the char is death
	if (decremented <= 0) {
		return -1;
	} else {
		// if not return current lives
		bchar->lives = decremented;
		return bchar->lives;
	}
}

int get_board_char_lives(Board_Character* bchar) {
	return bchar->lives;
}

int get_board_char_id(Board_Character bchar) {
	return bchar.custom_char_id;
}

bool is_char_death(Board_Character* bchar) {
	return bchar->lives == 0;
}

void change_board_char_to_none(Board_Character* bchar) {
	bchar->is_empty = true;
	bchar->type = empty_char;
	bchar->custom_char_id = -1;
	bchar->lives = -1;
}

bool is_empty_board_character(Board_Character* bchar) {
	return 	bchar->is_empty == true &&
			bchar->type == empty_char &&
			bchar->custom_char_id == -1 &&
			bchar->lives == -1 ? true : false;
}
