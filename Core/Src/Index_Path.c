/*
 * shot_index_path.c
 *
 *  Created on: Jan 28, 2023
 *      Author: kiarashvosough
 */


#include <Index_Path.h>

void init_index(Index_Path* index_path, int row, int column, Direction direction) {
	Index_Path new_index_path = {
			row,
			column,
			direction
	};

	*index_path = new_index_path;
}
