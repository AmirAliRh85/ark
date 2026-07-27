#include "../ark.h"
#include <stdbool.h>

#define ARK_STACK_MAX_SIZE      4096

ark_Stack* ark_Stack_create()
{
    ark_Stack* stack = malloc(sizeof(ark_Stack));
    
    stack->maxSize = ARK_STACK_MAX_SIZE;
    stack->size = 0;
    stack->top = NULL;

    return stack;
}

void ark_Stack_push(ark_Stack* stack , void* value)
{
    ark_SNode* top = malloc(sizeof(ark_SNode));
    top->prev = NULL;
    top->value = value;
    
    stack->size += 1;

    if (stack->top == NULL)
    {
        stack->top = top;
        return;
    }

    top->prev = stack->top;
    stack->top = top;
}

void ark_Stack_pop(ark_Stack* stack)
{
    if (stack->size == 0 || stack == NULL)
        return;

    ark_SNode* top = stack->top;

    stack->top = top->prev;
    stack->size -= 1;

    free(top);
}

void ark_Stack_destroy(ark_Stack* stack)
{
    while (stack->size >= 1)
    {
        ark_Stack_pop(stack);
    }

    free(stack);
}

void* ark_Stack_top(ark_Stack* stack)
{
    return stack->top->value;
}

int ark_Stack_size(ark_Stack* stack)
{
    return stack->size;
}

bool ark_Stack_isEmpty(ark_Stack* stack)
{
    if (stack->size <= 0)
        return true;

    return false;
}