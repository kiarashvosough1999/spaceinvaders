/*
 * pages.c
 *
 *  Created on: Feb 2, 2023
 *      Author: kiarashvosough
 */


#include <PageStuff/pages.h>

Page page_from_number(int id) {
	switch(id) {
		case 0:
			return splash;
		case 1:
			return about;
		case 2:
			return start_game;
		case 3:
			return enter_name;
		case 4:
			return choose_level;
		case 5:
			return game;
		default:
			return none_page;
	}
}
