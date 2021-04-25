#include <assert.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "stack.h"

struct Stack
{
    size_t elt_size;
    size_t maxsize;
    size_t top;
    void *items;
};

static struct Stack *stack_resize(struct Stack *stack, size_t maxsize);

struct Stack *stack_new(size_t elt_size)
{
    struct Stack *stack;

    assert(elt_size != 0);

    stack = (struct Stack *)malloc(sizeof(struct Stack));

    if (stack == NULL)
    {
        return NULL;
    }

    stack->elt_size = elt_size;
    stack->maxsize = 0;
    stack->top = 0;
    stack->items = NULL;

    return stack;
}

void stack_free(struct Stack *stack)
{
    assert(stack != NULL);

    free(stack->items);
    free(stack);
}

struct Stack *stack_push(struct Stack *stack, void *item)
{
    assert(stack != NULL);
    assert(item != NULL);

    if (stack->top == stack->maxsize)
    {
        if (stack->maxsize > SIZE_MAX >> 1)
        {
            return NULL;
        }

        stack = stack_resize(stack, (stack->maxsize << 1) + (stack->maxsize == 0));

        if (stack == NULL)
        {
            return NULL;
        }
    }

    memcpy(stack->items + stack->top * stack->elt_size, item, stack->elt_size);

    stack->top++;

    return stack;
}

struct Stack *stack_pop(struct Stack *stack, void *item)
{
    assert(stack != NULL);

    if (stack->top == 0)
    {
        return NULL;
    }

    if (stack->top << 1 == stack->maxsize >> 1)
    {
        stack = stack_resize(stack, stack->maxsize >> 1);

        if (stack == NULL)
        {
            return NULL;
        }
    }

    stack->top--;

    if (item != NULL)
    {
        memcpy(item, stack->items + stack->top * stack->elt_size, stack->elt_size);
    }

    return stack;
}

static struct Stack *stack_resize(struct Stack *stack, size_t maxsize)
{
    void *items;
    
    assert(stack != NULL);
    assert(maxsize != 0);

    if (maxsize > SIZE_MAX / stack->elt_size)
    {
        return NULL;
    }

    items = realloc(stack->items, maxsize * stack->elt_size);

    if (items == NULL)
    {
        return NULL;
    }

    stack->maxsize = maxsize;
    stack->items = items;

    return stack;
}
