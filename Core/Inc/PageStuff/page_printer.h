/*
 * page_printer.h
 *
 *  Created on: Jan 11, 2023
 *      Author: kiarashvosough
 */

#ifndef INC_PAGE_PRINTER_H_
#define INC_PAGE_PRINTER_H_

#include "pages.h"
#include "game_configuration_state.h"
#include "Managers/time_manager.h"
#include "board_characters.h"
#include <Index_Path.h>
#include <board_characters.h>
#include <DataStructures/page_stack.h>

typedef struct {
	Index_Path last_index_updated_on_screen;
	Page_Stack page_stack;
} Page_Printer;

void init_page_printer(Page_Printer* printer);

Page get_next_page(Page_Printer* printer);
Page get_current_page(Page_Printer* printer);
Page pop_page(Page_Printer* printer);

// print APIs
void print_splash_view(Page_Printer* printer);
void print_about_view(Page_Printer* printer, Time_Manager* time_manager, Game_Configuration_State* state);
void print_start_view(Page_Printer* printer);
void print_enter_name(Page_Printer* printer);
void print_choose_level_page(Page_Printer* printer);
void print_player_name(Page_Printer* printer, Game_Configuration_State* state);
void print_game_page(Page_Printer* printer, Board_Character** map);
void print_enemy_win_page(Page_Printer* printer);
void print_player_win_page(Page_Printer* printer, int point);

void update_game_board(Page_Printer* printer, Board_Character** map);
void update_game_board_on_screen(Page_Printer* printer, Board_Character** current_board);

#endif /* INC_PAGE_PRINTER_H_ */
