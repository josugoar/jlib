#include <stddef.h>

struct Stack;

struct Stack *stack_new(size_t elt_size);

void stack_free(struct Stack *stack);

struct Stack *stack_push(struct Stack *stack, void *item);

struct Stack *stack_pop(struct Stack *stack, void *item);
