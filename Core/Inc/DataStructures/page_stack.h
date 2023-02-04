/*
 * page_stack.h
 *
 *  Created on: Jan 31, 2023
 *      Author: kiarashvosough
 */

#ifndef INC_DATASTRUCTURES_PAGE_STACK_H_
#define INC_DATASTRUCTURES_PAGE_STACK_H_

#include <PageStuff/pages.h>

typedef struct {
	int top;
	Page inp_array[10];
} Page_Stack;

void stack_init(Page_Stack* stack);
void stack_push(Page_Stack* stack, Page page);
Page stack_pop(Page_Stack* stack);
Page stack_top(Page_Stack* stack);

#endif /* INC_DATASTRUCTURES_PAGE_STACK_H_ */
