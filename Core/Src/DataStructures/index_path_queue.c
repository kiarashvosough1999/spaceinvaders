/*
 * stack.c
 *
 *  Created on: Dec 5, 2022
 *      Author: kiarashvosough
 */


#include <DataStructures/index_path_queue.h>
#include "stdlib.h"

void queue_init(Index_Path_Queue* queue) {
	Index_Path_Queue new_queue = {
		-1,
		-1,
		{}
	};
	*queue = new_queue;
}

bool queue_is_queue_full(Index_Path_Queue* queue) {
	return queue->rear == 100 - 1 ? true : false;
}

bool queue_is_queue_empty(Index_Path_Queue* queue) {
	return queue->front == -1 ? true : false;
}

void queue_enQueue(Index_Path_Queue* queue, Index_Path value) {
  if (queue->rear == 100 - 1) {
	  // full
  }
  else {
    if (queue->front == -1) {
    	queue->front = 0;
    }
    queue->rear++;
    queue->items[queue->rear] = value;

  }
}

Index_Path queue_deQueue(Index_Path_Queue* queue) {

  if (queue->front == -1) {
	  // empty
	  Index_Path dummy = {-1, -1};
	  return dummy;
  }
  else {
	Index_Path temp_val = queue->items[queue->front];
	queue->front++;
    if (queue->front > queue->rear)
    	queue->front = queue->rear = -1;

    return temp_val;
  }
}

void queue_empty_queue(Index_Path_Queue* queue) {
	queue->front = -1;
	queue->rear = -1;
}

void queue_change_index_path_row_to_target(Index_Path_Queue* queue, int row, bool(* should_decrease)(Index_Path)) {
	for (int i = queue->front; i <= queue->rear; i++) {
		if(should_decrease(queue->items[i]) == true) {
			queue->items[i].row += row;
		}
	}
}

void queue_remove_index_paths(Index_Path_Queue* queue, bool(* should_be_removed)(Index_Path)) {
	Index_Path_Queue new_queue;
	queue_init(&new_queue);

	for (int i = queue->front; i <= queue->rear; i++) {
		if(should_be_removed(queue->items[i]) == false) {
			queue_enQueue(&new_queue, queue->items[i]);
		}
	}

	*queue = new_queue;
}

void queue_remove_index_path(Index_Path_Queue* queue, Index_Path index_path) {
	Index_Path_Queue new_queue;
	queue_init(&new_queue);

	for (int i = queue->front; i <= queue->rear; i++) {
		if(queue->items[i].column != index_path.column,
				queue->items[i].row != index_path.row,
				queue->items[i].direction != index_path.direction
		) {
			queue_enQueue(&new_queue, queue->items[i]);
		}
	}

	*queue = new_queue;
}

bool queue_has_item_with_index_path(Index_Path_Queue* queue, Index_Path index_path) {
	for (int i = queue->front; i <= queue->rear; i++) {
		if(queue->items[i].column == index_path.column,
				queue->items[i].row == index_path.row,
				queue->items[i].direction == index_path.direction
		) {
			return true;
		}
	}
	return false;
}

Index_Path queue_get_item_at_index(Index_Path_Queue* queue, int index) {
	return queue->items[index];
}

//int queue_rear_value(Queue* queue) {
//	if (queue->front == -1) {
//		// empty
//		return -1;
//	} else {
//		return queue->items[queue->rear].floor_index;
//	}
//}
