#include "environment.h"

#include <stdio.h>
#include <stdlib.h>


/**
 * initialise the environment struct
 */
environment *init_env(void)
{
    environment *env = malloc(sizeof(environment));
    if (env == NULL)
    {
        printf("go hard or go home; malloc failed in init_environment\n");
        exit(EXIT_FAILURE);
    }

    env->stack = init_stack();
    for (int i = 0; i < MAX_VARIABLE_SIZE; i++)
        env->variables[i] = 0;

    return env;
}

/**
 * frees the environment struct any data that was requested during runtime
 *
 * @env: the environment instance
 */
void free_env(environment *env)
{
    if (env == NULL)
    {
        printf("rest easy; environment uninitialised\n");
        return;
    }

    /* we don't really need to do this but I just want to */
    for (int i = 0; i < MAX_STACK_SIZE; i++)
        env->stack->items[i] = 0;

    for (int i = 0; i < MAX_VARIABLE_SIZE; i++)
        env->variables[i] = 0;

    free(env->stack);
    free(env);
}

/**
 * init_stack - initialises a stack structure to default values
 */
stack *init_stack(void)
{
    stack *retval = malloc(sizeof(stack));
    if (retval == NULL)
    {
        printf("go hard or go home; malloc failed in init_stack\n");
        exit(EXIT_FAILURE);
    }

    /* initialise all stack items to 0 */
    for (int i = 0; i < MAX_STACK_SIZE; i++)
        retval->items[i] = 0;

    retval->cur_stack_size = 0;
    retval->top = retval->items[retval->cur_stack_size];

    return retval;
}

/**
 * push - pushes a value onto the stack
 * @stack: the stack to push the value on
 * @value: the value to push
 */
void push(stack *stack, int value)
{
    /* check for a possible stack overflow */
    if (stack->cur_stack_size == MAX_STACK_SIZE)
    {
        printf("this should be an error for stack overflow\n");
        exit(EXIT_FAILURE);
    }

    /* using the current stack size as the index, 
     * we slot in the value into the items array
     * and increment the current stack size
     */
    stack->items[stack->cur_stack_size] = value;
    stack->top = stack->items[stack->cur_stack_size];
    stack->cur_stack_size += 1;
}

/**
 * pop - pop removes and returns the top value of the stack
 * @stack: the stack t pop the value from
 *
 * Return: returns the top value and removes it from the stack
 */
int pop(stack *stack)
{
    /* check for a possible stack underflow */
    if (stack->cur_stack_size == 0)
    {
        printf("this should be an error for stack underflow\n");
        exit(EXIT_FAILURE);
    }

    /* grab the top value using the current stack size as an index,
     * assign it to a variable that we will return and
     * then decrement the current stack size...
     * NB we don't really care about the value ahead because we'll
     * override it on the next push
     */
    int value = stack->items[stack->cur_stack_size - 1];
    stack->top = stack->items[stack->cur_stack_size - 1];
    stack->cur_stack_size -= 1;

    return value;
}
