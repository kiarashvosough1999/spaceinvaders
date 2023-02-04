/*
 * stack.c
 *
 *  Created on: Jan 31, 2023
 *      Author: kiarashvosough
 */

#include <DataStructures/page_stack.h>
#include <stdlib.h>
#include <main.h>

#define Array_Size(x)  (sizeof(x) / sizeof((x)[0]))

void stack_init(Page_Stack* stack) {
//	Page inp_array[10] = malloc(5 * sizeof(Page));
	Page_Stack new_stack = {
			-1,
			{}
	};
	*stack = new_stack;
}

void stack_push(Page_Stack* stack, Page page){
	stack->top += 1;
	stack->inp_array[stack->top] = page;
}

Page stack_top(Page_Stack* stack) {
	if (stack->top == -1) {
	    return none_page;
	}
	else {
		Page top = stack->inp_array[stack->top];
		return top;
	}
}

Page stack_pop(Page_Stack* stack){
    if (stack->top == -1) {
        return none_page;
    }
    else{
        stack->top -= 1;
        return stack->inp_array[stack->top];
    }
}

//void show()
//{
//    if (top == -1)
//    {
//        printf("\nUnderflow!!");
//    }
//    else
//    {
//        printf("\nElements present in the stack: \n");
//        for (int i = top; i >= 0; --i)
//            printf("%d\n", inp_array[i]);
//    }
//}
