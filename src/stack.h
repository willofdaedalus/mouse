/* stacks are the essential component of the mouse interpreter. they operate
 * on a Last In First Out basis which also means the first item or value
 * added to the stack is always the last to removed.
 *
 * On the design of the stack, we could go the traditional way of doing things
 * and make the stack a linked list or we could go another way of doing things
 * and just make the entire 
 *
 * Based on that I've decided to make the stack an array of items with a count
 * https://en.wikipedia.org/wiki/Stack_(abstract_data_type)
 */
#ifndef STACK_H
#define STACK_H

#include <stdlib.h>

#define MAX_STACK_SIZE                      32

typedef struct 
{
    size_t cur_stack_size;
    int items[MAX_STACK_SIZE];
} stack;

stack *init_stack(void);
void push(stack *stack, int value);
int pop(stack *stack);


#endif
