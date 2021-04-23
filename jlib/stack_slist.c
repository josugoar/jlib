#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "stack.h"

struct Frame
{
    void *item;
    struct Frame *next;
};

struct Stack
{
    size_t elt_size;
    struct Frame *head;
};

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
    stack->head = NULL;

    return stack;
}

void stack_free(struct Stack *stack)
{
    struct Frame *head;

    assert(stack != NULL);

    head = stack->head;

    while (head != NULL)
    {
        struct Frame *frame;

        frame = head;
        head = head->next;

        free(frame->item);
        free(frame);
    }

    free(stack);
}

struct Stack *stack_push(struct Stack *stack, void *item)
{
    struct Frame *head;

    assert(stack != NULL);
    assert(item != NULL);

    head = (struct Frame *)malloc(sizeof(struct Frame));

    if (head == NULL)
    {
        return NULL;
    }

    head->item = malloc(stack->elt_size);

    if (head->item == NULL)
    {
        free(head);
        return NULL;
    }

    head->next = stack->head;
    stack->head = head;

    memcpy(head->item, item, stack->elt_size);

    return stack;
}

struct Stack *stack_pop(struct Stack *stack, void *item)
{
    struct Frame *head;

    assert(stack != NULL);

    if (stack->head == NULL)
    {
        return NULL;
    }

    head = stack->head;
    stack->head = head->next;

    if (item != NULL)
    {
        memcpy(item, head->item, stack->elt_size);
    }

    free(head->item);
    free(head);

    return stack;
}
