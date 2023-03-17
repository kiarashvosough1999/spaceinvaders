/*
 * keypad_manager.c
 *
 *  Created on: Jan 10, 2023
 *      Author: kiarashvosough
 */

#include "Managers/keypad_manager.h"
#include "main.h"
#include "app_action.h"

static int get_start_char_offset_for_button(KeyPad_Manager *manager, Buttons button);


void init_keypad_manager(KeyPad_Manager *manager) {
	KeyPad_Manager new_manager = {
			zero,
			0
	};
	*manager = new_manager;
}


void find_button(KeyPad_Manager *manager, uint16_t GPIO_Pin) {

	extern App_Action action;
//	Buttons b;

	for (int i = 0; i < 4; i++) {
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_4, 0);
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_5, 0);
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_6, 0);
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_7, 0);

		if (i == 0) { // checking row 0
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_7, 1);
			if (HAL_GPIO_ReadPin(GPIOD, GPIO_Pin) == 1) { // column 3
				if (GPIO_Pin == GPIO_PIN_0) { // A
//					b = A;
					button_pressed(&action, A);
					break;
				} else if (GPIO_Pin == GPIO_PIN_1) { // 3
//					b = three;
					button_pressed(&action, three);
					break;
				} else if (GPIO_Pin == GPIO_PIN_2) { // 2
//					b = two;
					button_pressed(&action, two);
					break;
				} else if (GPIO_Pin == GPIO_PIN_3) { // 1
//					b = one;
					button_pressed(&action, one);
					break;
				}
			}
		} else if (i == 1) { // checking row 1
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_6, 1);
			if (HAL_GPIO_ReadPin(GPIOD, GPIO_Pin) == 1) { // column 2
				if (GPIO_Pin == GPIO_PIN_0) { // B
//					b = B;
					button_pressed(&action, B);
					break;
				} else if (GPIO_Pin == GPIO_PIN_1) { //
//					b = six;
					button_pressed(&action, six);
					break;
			    } else if (GPIO_Pin == GPIO_PIN_2) { //
//			    	b = five;
			    	button_pressed(&action, five);
			    	break;
				} else if (GPIO_Pin == GPIO_PIN_3) { //
//					b = four;
					button_pressed(&action, four);
					break;
				}
			}
		} else if (i == 2) { // checking row 2
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_5, 1);
			if (HAL_GPIO_ReadPin(GPIOD, GPIO_Pin) == 1) { // column 1
				if (GPIO_Pin == GPIO_PIN_0) { // C
//					b = C;
					button_pressed(&action, C);
					break;
				} else if (GPIO_Pin == GPIO_PIN_1) { //
//					b = nine;
					button_pressed(&action, nine);
					break;
			    } else if (GPIO_Pin == GPIO_PIN_2) { //
//			    	b = eight;
			    	button_pressed(&action, eight);
			    	break;
				} else if (GPIO_Pin == GPIO_PIN_3) { //
//					b = seven;
					button_pressed(&action, seven);
					break;
				}
			}
		} else if (i == 3) { // checking row 3
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_4, 1);
			if (HAL_GPIO_ReadPin(GPIOD, GPIO_Pin) == 1) { // column 0
				if (GPIO_Pin == GPIO_PIN_0) { // D
//					b = D;
					button_pressed(&action, D);
					break;
				} else if (GPIO_Pin == GPIO_PIN_1) {
//					b = hashtag;
					button_pressed(&action, hashtag);
					break;
			    } else if (GPIO_Pin == GPIO_PIN_2) {
//			    	b = zero;
			    	button_pressed(&action, zero);
			    	break;
				} else if (GPIO_Pin == GPIO_PIN_3) { // *
//					b = star;
					button_pressed(&action, star);
					break;
				}
			}
		}
	}
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_4, 1);
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_5, 1);
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_6, 1);
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_7, 1);
	while(HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_0));
}

void set_pressed_button(KeyPad_Manager *manager, Buttons button) {
//	extern char dest[10];
//	strncpy(dest, "", sizeof(dest));
	if(button > 9) { return; }

//    char c[2];
//    itoa(button, c, 10);
//    char c1[2];
//    itoa(manager->current_pressed_buttons, c1, 10);
//    strcat(dest, c);
//    strcat(dest, c1);
//    strcat(dest, "\n");

	if (button != manager->current_pressed_buttons) {
		manager->current_pressed_buttons = button;
		manager->char_offset = 0;

	} else {
		if (button == seven || button == nine) {
			if (manager->char_offset >= 3) {
				manager->char_offset = 0;
			} else {
				manager->char_offset++;
			}
		} else {
			if (manager->char_offset >= 2) {
				manager->char_offset = 0;
			} else {
				manager->char_offset++;
			}
		}
//	    extern char dest[10];
//	    char c3[2];
//	    int i = manager->char_offset;
//	    itoa(i, c3, 10);
//	    strcat(dest, c3);
//	    strcat(dest, "el\n");
	}
}

char get_alphabetic_char_with_offset(KeyPad_Manager *manager) {
//	extern char dest[10];
//	strncpy(dest, "", sizeof(dest));
    char alph[27];
    int x = manager->char_offset + get_start_char_offset_for_button(manager, manager->current_pressed_buttons);
    char *ptr;
    ptr = alph;
    *ptr = x + 'A';
    char m = *ptr;

//    extern char dest[10];
//    strcat(dest, ptr);
//    char c[2];
//    itoa(x,c, 10);
//    strcat(dest, c);
//    strcat(dest, "|\n");

    return m;
}

// private APIs

static int get_start_char_offset_for_button(KeyPad_Manager *manager, Buttons button) {

	switch (button) {
	case two: // 0 1 2
		return 0;
	case three: // 3 4 5
		return 3;
	case four: // 6 7 8
		return 6;
	case five:// 9 10 11
		return 9;
	case six: // 12 13 14
		return 12;
	case seven: // 15 16 17 18
		return 15;
	case eight: // 19 20 21
		return 19;
	case nine: // 22 23 24 25
		return 22;
	default:
		return -1;

	}
}









