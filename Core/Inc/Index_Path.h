/*
 * shot_index_path.h
 *
 *  Created on: Jan 28, 2023
 *      Author: kiarashvosough
 */

#ifndef INC_INDEX_PATH_H_
#define INC_INDEX_PATH_H_

typedef enum {
	up,
	down,
	left,
	right
} Direction;

typedef struct {
	int row;
	int column;
	Direction direction;
} Index_Path;

void init_index(Index_Path* index_path, int row, int column, Direction direction);

#endif /* INC_INDEX_PATH_H_ */
