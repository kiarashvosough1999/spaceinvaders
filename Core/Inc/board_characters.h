/*
 * board_characters.h
 *
 *  Created on: Jan 27, 2023
 *      Author: kiarashvosough
 */

#ifndef INC_BOARD_CHARACTERS_H_
#define INC_BOARD_CHARACTERS_H_

#include <custom_character.h>
#include <bool.h>
#include <game_level.h>

typedef struct {
	Custom_Character type;
	int custom_char_id;
    int lives;
    bool is_empty;
} Board_Character;

void init_board_character(Board_Character* bchar, Custom_Character type, Game_Level level);

int get_board_char_id(Board_Character bchar);
int get_board_char_lives(Board_Character* bchar);
bool is_char_death(Board_Character* bchar);

// return current lives after decrement, if zero returns -1
int decrement_1_board_char_lives(Board_Character* bchar);

void change_board_char_to_none(Board_Character* bchar);

bool is_empty_board_character(Board_Character* bchar);

#endif /* INC_BOARD_CHARACTERS_H_ */
