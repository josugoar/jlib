#include <stddef.h>

struct Stack;

struct Stack *stack_new(size_t);

void stack_free(struct Stack *);

struct Stack *stack_push(struct Stack *, void *);

struct Stack *stack_pop(struct Stack *, void *);
