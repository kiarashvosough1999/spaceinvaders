/*
 * page_printer.c
 *
 *  Created on: Jan 11, 2023
 *      Author: kiarashvosough
 */


#include "main.h"
#include "PageStuff/page_printer.h"
#include "LiquidCrystal.h"
#include <string.h>
#include "stdio.h"

void clean_view(int line) {
	char* empty_line = "                    ";
	if (line == -1) {
		for (int i = 0;  i < 4; ++ i) {
			setCursor(0, line);
			print(empty_line);
		}
	}
	else {
		setCursor(0, line);
		print(empty_line);
	}
}

// initialization

void init_page_printer(Page_Printer* printer) {

	// create stack to keep track of pushes so we can pop.
	Page_Stack page_stack;
	stack_init(&page_stack);

	Index_Path index;
	init_index(&index, 0, 0, up);

	Page_Printer new_printer = {
			index,
			page_stack
	};
	*printer = new_printer;
}

// print APIs

void print_splash_view(Page_Printer* printer) {
	stack_push(&printer->page_stack, splash);
	clear();
	setCursor(6, 0);
	print("Welcome");
	setCursor(9, 1);
	print("To");
	setCursor(3, 2);
	print("Space Invaders");
}

void print_about_view(Page_Printer* printer, Time_Manager* time_manager, Game_Configuration_State* state) {

	if (stack_top(&printer->page_stack) != about) {
		stack_push(&printer->page_stack, about);
		clean_view(0);
		clean_view(2);
	}

	char date_string[10];
	char time_string[10];

	RTC_DateTypeDef date;
	RTC_TimeTypeDef time;
	get_system_date(time_manager, &date);
	get_system_time(time_manager, &time);

	setCursor(0, 1);
	print(state->player_name);
	for (int i = strlen(state->player_name); i < 20; i++) {
		setCursor(i, 1);
		print(" ");
	}

	setCursor(0, 3);
	sprintf(date_string, "%d/%d/%d", date.Year, date.Month, date.Date);
	print(date_string);

	setCursor(10, 3);
	sprintf(time_string, "%d:%d:%d", time.Hours, time.Minutes, time.Seconds);
	if (time.Seconds < 10) {
		strcat(time_string, "    ");
	}
	print(time_string);
}

void print_start_view(Page_Printer* printer) {
	stack_push(&printer->page_stack, start_game);
	clear();
	setCursor(6, 0);
	print("A. about");
	setCursor(6, 1);
	print("C. start");
}

void print_enter_name(Page_Printer* printer) {
	stack_push(&printer->page_stack, enter_name);
	clear();
	setCursor(0, 0);
	print("A.choose level");
	setCursor(0, 1);
	print("Enter Name:");
}

void print_player_name(Page_Printer* printer, Game_Configuration_State* state) {
	setCursor(0, 2);
	print(state->player_name);
}

void print_choose_level_page(Page_Printer* printer) {
	if (stack_top(&printer->page_stack) != choose_level) {
		stack_push(&printer->page_stack, choose_level);
	}
	clear();
	setCursor(0, 0);
	print("A.start game");
	setCursor(0, 1);
	print("Enter Level:");

	setCursor(0, 2);
	print("1. easy");

	setCursor(8, 2);
	print("2. normal");

	setCursor(0, 3);
	print("3. hard");
}

void print_game_page(Page_Printer* printer, Board_Character** map) {
	if (stack_top(&printer->page_stack) != game) {
		stack_push(&printer->page_stack, game);
		clear();
	}
	//   0123
	// | ++++ | 9
	// | ++++ | 8
	// | ++++ | 7
	// | ++++ | 6
	// | ++++ | 5
	// | ++++ | 4
	// | ++++ | 3
	// | ++++ | 2
	// | ++++ | 1
	// | ++++ | 0
	for (int row = 0; row < 20; row++) {
		for (int col = 0; col < 4; col++) {
			// col - row
			setCursor(row, col);
			if (map[row][col].is_empty == false) {
				write(get_board_char_id(map[row][col]));
			} else {
				print(" ");
			}
		}
	}
}

void print_enemy_win_page(Page_Printer* printer) {
	clear();
	setCursor(5, 2);
	print("You Lost:)");
}

void print_player_win_page(Page_Printer* printer, int point) {
	clear();
	setCursor(5, 1);
	print("You Win");

	setCursor(5, 2);
	print("points");
	char snum[10];
	itoa(point, snum, 10);
	print(snum);
}

//void update_game_board(Page_Printer* printer, Board_Character** map) {
//	int column = printer->last_index_updated_on_screen.column;
//	int row = printer->last_index_updated_on_screen.row;
//
//	extern char dest[10];
//	char num[3];
//	itoa(row, num, 10);
//	strcat(dest, num);
//
//	setCursor(row, column);
//
//	if (map[row][column].is_empty == false) {
//		// column - row
//		write(get_board_char_id(map[row][column]));
//		HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_13);
//	} else {
//		print(" ");
//	}
//
//	if (row == 19) {
//		row = 0;
//	} else {
//		row += 1;
//	}
//
//	if (column == 3) {
//		column = 0;
//	} else {
//		column += 1;
//	}
//
//	Index_Path last_index_updated_on_screen = { row, column, up };
//	printer->last_index_updated_on_screen = last_index_updated_on_screen;
//}

Page get_next_page(Page_Printer* printer) {
	return (Page)(stack_top(&printer->page_stack) + 1);
}

Page get_current_page(Page_Printer* printer) {
	return stack_top(&printer->page_stack);
}

Page pop_page(Page_Printer* printer) {
	return stack_pop(&printer->page_stack);
}

