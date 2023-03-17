/*
 * app_action.c
 *
 *  Created on: Jan 11, 2023
 *      Author: kiarashvosough
 */


#include "app_action.h"
#include "PageStuff/page_printer.h"
#include "PageStuff/pages.h"
#include "string.h"
#include <board_characters.h>

// declarations

static void button_one_action_handler(App_Action* action);
static void button_two_action_handler(App_Action* action);
static void button_three_action_handler(App_Action* action);
static void button_four_action_handler(App_Action* action);
static void button_six_action_handler(App_Action* action);

static void button_A_action_handler(App_Action* action);
static void button_B_action_handler(App_Action* action);
static void button_C_action_handler(App_Action* action);
static void button_D_action_handler(App_Action* action);
static void change_page(App_Action* action, Page page);

static void player_is_about_to_die(void);
static void there_is_only_3_enemies_left(void);
static void player_did_win(void);
static void enemies_did_win(void);
static void enemies_got_shot(int point);

// initialization

void init_app_action(
		App_Action* action,
		Time_Manager* time_manager,
		Game_Configuration_State* game_config_state,
		KeyPad_Manager* keypad_manager,
		Page_Printer* printer,
		UART_Manager* uart_manager,
		Buzzer_Player* player,
		ADC_Manager* adc_manager
		) {
	App_Action new_action = {
			time_manager,
			game_config_state,
			keypad_manager,
			uart_manager,
			printer,
			player,
			adc_manager,
			NULL
	};
	*action = new_action;
}

// actions begin

void timer_2_did_triggered(App_Action* action, int current_time) {

	Page current_page = get_current_page(action->printer);
	// when 3 sec pass, we change page from splash to next page
	if (current_page == splash && app_startup_duration(action->game_config_state) > 3000) {
		change_page(action, start_game);
	} else if(current_page == about) { /// for handle refreshing the time and date
		change_page(action, about);
	} else if(current_page == game) {
		time_did_passed(action->logic, current_time, action->game_config_state->hardness_level);
		print_game_page(action->printer, action->logic->current_board);
	}
}

void uart_did_received_message(App_Action* action) {
	if(get_current_page(action->printer) == enter_name) {
		char name[10];
		get_received_message(action->uart_manager, name);

		set_player_name(action->game_config_state, name);
		print_player_name(action->printer, action->game_config_state);
	}
}

void button_pressed(App_Action* action, Buttons button) {
	set_pressed_button(action->keypad_manager, button);
	switch(button) {
	case one:
		button_one_action_handler(action);
		break;
	case two:
		button_two_action_handler(action);
		break;
	case three:
		button_three_action_handler(action);
		break;
	case four:
		button_four_action_handler(action);
		break;
	case six:
		button_six_action_handler(action);
		break;
	case A:
		button_A_action_handler(action);
		break;
	case B:
		button_B_action_handler(action);
		break;
	case C:
		button_C_action_handler(action);
		break;
	case D:
		button_D_action_handler(action);
		break;
	default:
		break;
	}
}

// private APIs

static void load_game_logic(App_Action* action) {
	// load game page before loading game.
	extern Game_Logic logic;
	init_game_logic(&logic, action->game_config_state->hardness_level);

	logic.player_is_about_to_die = player_is_about_to_die;
	logic.there_is_only_3_enemies_left = there_is_only_3_enemies_left;
	logic.player_did_win = player_did_win;
	logic.enemies_did_win = enemies_did_win;
	logic.enemies_got_shot = enemies_got_shot;
	logic.enemies_got_shot = enemies_got_shot;

	action->logic = &logic;
	change_page(action, game);
}

static void change_page(App_Action* action, Page page) {
	switch(page) {
	case splash:
		print_splash_view(action->printer);
		break;
	case about:
		print_about_view(action->printer, action->time_manager, action->game_config_state);
		break;
	case start_game:
		print_start_view(action->printer);
		break;
	case enter_name:
		print_enter_name(action->printer);
		print_player_name(action->printer, action->game_config_state);
		break;
	case choose_level:
		buzzer_play(action->player);
		print_choose_level_page(action->printer);
		break;
	case game:;
	    adc_stop(action->adc_manager);
	    buzzer_pause(action->player);
		Board_Character** board = action->logic->current_board;
		print_game_page(action->printer, board);
		break;
	case player_win:
		buzzer_play(action->player);
		adc_start(action->adc_manager);
		print_player_win_page(action->printer, action->game_config_state->player_points);
		break;
	case enemy_win:
		print_enemy_win_page(action->printer);
		break;
	default:
		break;
	}
}

static void button_one_action_handler(App_Action* action) {
	if (get_current_page(action->printer) == choose_level) {
		set_hardness_level(action->game_config_state, easy);
		load_game_logic(action);
	}
}

static void button_two_action_handler(App_Action* action) {
	if (get_current_page(action->printer) == choose_level) {
		set_hardness_level(action->game_config_state, normal);
		load_game_logic(action);
	}
}

static void button_three_action_handler(App_Action* action) {
	Page current_page = get_current_page(action->printer);
	if (current_page == choose_level) {
		set_hardness_level(action->game_config_state, hard);
		load_game_logic(action);
	}
}

static void button_four_action_handler(App_Action* action) {
	Page current_page = get_current_page(action->printer);
	if (current_page == game) {
		user_should_move(action->logic, left);
	}
}

static void button_six_action_handler(App_Action* action) {
	Page current_page = get_current_page(action->printer);
	if (current_page == game) {
		user_should_move(action->logic, right);
	}
}

static void button_A_action_handler(App_Action* action) {
	// check if we are in the middle of game

	Page current_page = get_current_page(action->printer);

	if (current_page == start_game) {
		change_page(action, about);
	} else if (current_page == enter_name) {
		//  && action->game_config_state->is_player_name_set == true
		// check if we can move to next page or not
		Page next_page = get_next_page(action->printer);
		change_page(action, next_page);
	} else {
		return;
	}
}

static void button_B_action_handler(App_Action* action) {
	Page last_page = pop_page(action->printer);
	if (last_page == none_page) { return; }
	change_page(action, last_page);
}

static void button_C_action_handler(App_Action* action) {
	Page current_page = get_current_page(action->printer);
	if (current_page == start_game) {
		Page next_page = get_next_page(action->printer);
		change_page(action, next_page);
	}
}

static void button_D_action_handler(App_Action* action) {
	Page current_page = get_current_page(action->printer);
	if (current_page == game) {
		user_did_shot(action->logic, action->game_config_state->hardness_level);
	} else if(current_page == enter_name) {
		char letter = get_alphabetic_char_with_offset(action->keypad_manager);
		char* name = action->game_config_state->player_name;
		strncat(name, &letter, 1);
		set_player_name(action->game_config_state, name);
		change_page(action, enter_name);
	}
}

// callbacks from logic

static void player_is_about_to_die(void) {
	extern App_Action action;
	char* message = "you have 3 life left.";
	send_message_through_uart_unlimited(&action.uart_manager, message);
}

static void there_is_only_3_enemies_left(void) {
	extern App_Action action;
	char* message = "you have 3 enemies left";
	send_message_through_uart_unlimited(&action.uart_manager, message);
}

static void player_did_win(void) {
	extern App_Action action;
	char* message = "You won.";
	send_message_through_uart_unlimited(&action.uart_manager, message);
	change_page(&action, player_win);
}

static void enemies_did_win(void) {
	extern App_Action action;
	char* message = "You lost.";
	send_message_through_uart_unlimited(&action.uart_manager, message);
	change_page(&action, enemy_win);
}

static void enemies_got_shot(int point) {
	extern App_Action action;
	add_point_(&action.game_config_state, point);
}



