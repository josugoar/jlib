#include <assert.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "heap.h"

struct Heap
{
    size_t elt_size;
    size_t maxsize;
    void *items;
};

static struct Heap *heap_resize(struct Heap *heap, size_t maxsize);

struct Heap *heap_new(size_t elt_size)
{
    struct Heap *heap;

    heap = (struct Heap *)malloc(sizeof(*heap));

    if (heap == NULL)
    {
        return NULL;
    }

    heap->elt_size = elt_size;
    heap->maxsize = 0;
    heap->items = NULL;

    return heap;
}

void heap_free(struct Heap *heap)
{
    assert(heap != NULL);

    free(heap->items);
    free(heap);
}

struct Heap *heap_store(struct Heap *heap, size_t key, void *value)
{
    assert(heap != NULL);
    assert(value != NULL);

    if (key >= heap->maxsize)
    {
        if (key > SIZE_MAX - 1)
        {
            return NULL;
        }

        if (heap_resize(heap, key + 1) == NULL)
        {
            return NULL;
        }
    }

    memcpy(heap->items + key * heap->elt_size, value, heap->elt_size);

    return heap;
}

struct Heap *heap_retrieve(struct Heap *heap, size_t key, void *value)
{
    assert(heap != NULL);

    if (key >= heap->maxsize)
    {
        return NULL;
    }

    memcpy(value, heap->items + key * heap->elt_size, heap->elt_size);

    return heap;
}

static struct Heap *heap_resize(struct Heap *heap, size_t maxsize)
{
    void *items;

    assert(heap != NULL);
    assert(maxsize != 0);

    if (maxsize > SIZE_MAX / heap->elt_size)
    {
        return NULL;
    }

    items = realloc(heap->items, maxsize * heap->elt_size);

    if (items == NULL)
    {
        return NULL;
    }

    heap->maxsize = maxsize;
    heap->items = items;

    return heap;
}
