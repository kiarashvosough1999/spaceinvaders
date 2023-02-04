/*
 * game_level.c
 *
 *  Created on: Feb 3, 2023
 *      Author: kiarashvosough
 */


#include <game_level.h>

int get_enemies_count(Game_Level level) {
	int sens = get_senior_enemies_count(level);
	int mids = get_mid_enemies_count(level);
	int juns = get_junior_enemies_count(level);

	return (sens + mids + juns);
}

int get_enemies_rows_count(Game_Level level) {
	int sens = get_senior_enemies_count(level);
	int mids = get_mid_enemies_count(level);
	int juns = get_junior_enemies_count(level);

	return (sens + mids + juns)/4;
}

int get_enemies_movement_freq(Game_Level level) {
	switch(level) {
	case easy:
		return 15000;
	case normal:
		return 10000;
	case hard:
		return 5000;
	}
	return -1;
}

int get_senior_enemies_count(Game_Level level) {
	switch(level) {
	case easy:
		return 4;
	case normal:
		return 8;
	case hard:
		return 12;
	}
	return -1;
}

int get_mid_enemies_count(Game_Level level) {
	switch(level) {
	case easy:
		return 4;
	case normal:
		return 8;
	case hard:
		return 12;
	}
	return -1;
}

int get_junior_enemies_count(Game_Level level) {
	switch(level) {
	case easy:
		return 4;
	case normal:
		return 8;
	case hard:
		return 12;
	}
	return -1;
}

int get_character_lives(Custom_Character name, Game_Level level) {
	switch (name) {
	case boss:
		return 15;
	case senior:
		return 7;
	case mid:
		return 5;
	case junior:
		return 1;
	case player_1:
		switch(level) {
		case easy:
			return 7;
		case normal:
			return 5;
		case hard:
			return 3;
		}
	default:
		return -1;
	}
}
