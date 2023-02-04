/*
 * index_path_queue.h
 *
 *  Created on: Dec 5, 2022
 *      Author: kiarashvosough
 */

#ifndef INC_QUEUE_H_
#define INC_QUEUE_H_

#include <Index_Path.h>
#include "bool.h"

typedef struct {
	int front;
	int rear;
	Index_Path items[100];
} Index_Path_Queue;

void queue_init(Index_Path_Queue* queue);

void queue_enQueue(Index_Path_Queue* queue, Index_Path value);

Index_Path queue_deQueue(Index_Path_Queue* queue);

bool queue_is_queue_full(Index_Path_Queue* queue);

bool queue_is_queue_empty(Index_Path_Queue* queue);

void queue_empty_queue(Index_Path_Queue* queue);

bool queue_has_item_with_floor_index(Index_Path_Queue* queue, int index);

void queue_change_index_path_row_to_target(Index_Path_Queue* queue, int row, bool(* should_decrease)(Index_Path));

void queue_remove_index_paths(Index_Path_Queue* queue, bool(* should_be_removed)(Index_Path));

int queue_rear_value(Index_Path_Queue* queue);

void queue_remove_index_path(Index_Path_Queue* queue, Index_Path index_path);

bool queue_has_item_with_index_path(Index_Path_Queue* queue, Index_Path index_path);

Index_Path queue_get_item_at_index(Index_Path_Queue* queue, int index);

#endif /* INC_QUEUE_H_ */
