/*
 * keypad_manager.c
 *
 *  Created on: Jan 10, 2023
 *      Author: kiarashvosough
 */

#include "Managers/keypad_manager.h"
#include "main.h"
#include "app_action.h"

void init_keypad_manager(KeyPad_Manager *manager) {
	KeyPad_Manager new_manager = {};
	*manager = new_manager;
}


void find_button(KeyPad_Manager *manager, uint16_t GPIO_Pin) {

	extern App_Action action;

	for (int i = 0; i < 4; i++) {
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_4, 0);
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_5, 0);
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_6, 0);
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_7, 0);

		if (i == 0) { // checking row 0
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_7, 1);
			if (HAL_GPIO_ReadPin(GPIOD, GPIO_Pin) == 1) { // column 3
				if (GPIO_Pin == GPIO_PIN_0) { // A
					button_pressed(&action, A);
					break;
				} else if (GPIO_Pin == GPIO_PIN_1) { // 3
					button_pressed(&action, three);
					break;
				} else if (GPIO_Pin == GPIO_PIN_2) { // 2
					button_pressed(&action, two);
					break;
				} else if (GPIO_Pin == GPIO_PIN_3) { // 1
					button_pressed(&action, one);
					break;
				}
			}
		} else if (i == 1) { // checking row 1
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_6, 1);
			if (HAL_GPIO_ReadPin(GPIOD, GPIO_Pin) == 1) { // column 2
				if (GPIO_Pin == GPIO_PIN_0) { // B
					button_pressed(&action, B);
					break;
				} else if (GPIO_Pin == GPIO_PIN_1) { //
					button_pressed(&action, six);
					break;
			    } else if (GPIO_Pin == GPIO_PIN_2) { //
			    	button_pressed(&action, five);
			    	break;
				} else if (GPIO_Pin == GPIO_PIN_3) { //
					button_pressed(&action, four);
					break;
				}
			}
		} else if (i == 2) { // checking row 2
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_5, 1);
			if (HAL_GPIO_ReadPin(GPIOD, GPIO_Pin) == 1) { // column 1
				if (GPIO_Pin == GPIO_PIN_0) { // C
					button_pressed(&action, C);
					break;
				} else if (GPIO_Pin == GPIO_PIN_1) { //
					button_pressed(&action, nine);
					break;
			    } else if (GPIO_Pin == GPIO_PIN_2) { //
			    	button_pressed(&action, eight);
			    	break;
				} else if (GPIO_Pin == GPIO_PIN_3) { //
					button_pressed(&action, seven);
					break;
				}
			}
		} else if (i == 3) { // checking row 3
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_4, 1);
			if (HAL_GPIO_ReadPin(GPIOD, GPIO_Pin) == 1) { // column 0
				if (GPIO_Pin == GPIO_PIN_0) { // D
					button_pressed(&action, D);
					break;
				} else if (GPIO_Pin == GPIO_PIN_1) {
					button_pressed(&action, hashtag);
					break;
			    } else if (GPIO_Pin == GPIO_PIN_2) {
			    	button_pressed(&action, zero);
			    	break;
				} else if (GPIO_Pin == GPIO_PIN_3) { // *
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
