/*
 * app_action.h
 *
 *  Created on: Jan 11, 2023
 *      Author: kiarashvosough
 */

#ifndef INC_APP_ACTION_H_
#define INC_APP_ACTION_H_

#include "Managers/time_manager.h"
#include "game_configuration_state.h"
#include "Managers/keypad_manager.h"
#include "PageStuff/page_printer.h"
#include "Managers/uart_manager.h"
#include <game_logic.h>
#include <Buzzer/buzzer_player.h>
#include <Managers/adc_manager.h>

typedef struct {
	Time_Manager* time_manager;
	Game_Configuration_State* game_config_state;
	KeyPad_Manager* keypad_manager;
	UART_Manager* uart_manager;
	Page_Printer* printer;
	Buzzer_Player* player;
	ADC_Manager* adc_manager;
	Game_Logic* logic;
} App_Action;

void init_app_action(App_Action* action,
		Time_Manager* time_manager,
		Game_Configuration_State* game_config_state,
		KeyPad_Manager* keypad_manager,
		Page_Printer* printer,
		UART_Manager* uart_manager,
		Buzzer_Player* player,
		ADC_Manager* adc_manager
		);

void timer_2_did_triggered(App_Action* action, int current_time);

void button_pressed(App_Action* action, Buttons button);

void uart_did_received_message(App_Action* action);

#endif /* INC_APP_ACTION_H_ */
