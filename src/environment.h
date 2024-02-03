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

#define MAX_STACK_SIZE                              32
#define MAX_VARIABLE_SIZE                           130
#define ASCII_OFFSET                                65

/**
 * stack struct that keeps track of the global stack in use during programs
 * 
 * @cur_stack_size: the current number of items in the stack currently to
 * check for possible overflows and underflows when popping and pushing
 * values
 * @items; an array used to represent the stack
 */
typedef struct 
{
    int top; /* this is for debugging purposes only */
    size_t cur_stack_size;
    int items[MAX_STACK_SIZE];
} stack;


/**
 * environment contains necessary information needed during the execution
 * and running of programs in the mouse language
 *
 * @stack: a pointer to a stack struct
 * @variables: the global array of variables allowed in the program;
 * indicated by the MAX_VARIABLE_SIZE preprocessor
 */
typedef struct
{
    stack *stack;
    int variables[MAX_VARIABLE_SIZE];
} environment;


environment *init_env(void);
void free_env(environment *env);
stack *init_stack(void);
void push(stack *stack, const int value);
int pop(stack *stack);


#endif
