/*
 * pages.h
 *
 *  Created on: Jan 11, 2023
 *      Author: kiarashvosough
 */

#ifndef INC_PAGES_H_
#define INC_PAGES_H_

typedef enum {
	none_page = -1,
	splash = 0,
	about = 1,
	start_game  =2,
	enter_name = 3,
	choose_level = 4,
	game = 5,
	player_win = 6,
	enemy_win = 7
} Page;

Page page_from_number(int id);

#endif /* INC_PAGES_H_ */
