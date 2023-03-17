/*
 * keypad_manager.h
 *
 *  Created on: Jan 10, 2023
 *      Author: kiarashvosough
 */

#ifndef INC_KEYPAD_MANAGER_H_
#define INC_KEYPAD_MANAGER_H_

#include "main.h"

typedef enum {
	zero, one, two, three, four, five, six, seven, eight, nine, A, B, C, D, hashtag, star
} Buttons;

typedef struct {
	Buttons current_pressed_buttons;
	int char_offset; // 0...2
} KeyPad_Manager;

void init_keypad_manager(KeyPad_Manager *manager);
void find_button(KeyPad_Manager *manager, uint16_t GPIO_Pin);
void set_pressed_button(KeyPad_Manager *manager, Buttons button);
char get_alphabetic_char_with_offset(KeyPad_Manager *manager);

#endif /* INC_KEYPAD_MANAGER_H_ */
