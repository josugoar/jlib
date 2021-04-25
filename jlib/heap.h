#include <stddef.h>

struct Heap;

struct Heap *heap_new(size_t elt_size);

void heap_free(struct Heap *heap);

struct Heap *heap_store(struct Heap *heap, size_t key, void *value);

struct Heap *heap_retrieve(struct Heap *heap, size_t key, void *value);
