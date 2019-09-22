#include <stdio.h>
#include <stdlib.h>

#include "vector.h"

#define VECTOR_INIT_CAPACITY 5

void vector_init(struct vector *v)
{
    v->capacity = VECTOR_INIT_CAPACITY;
    v->count = 0;
    v->items = malloc(sizeof(void *) * v->capacity);
}

int vector_total(struct vector *v)
{
    return v->count;
}

static void vector_resize(struct vector *v, int capacity)
{
    void **items = realloc(v->items, sizeof(void *) * capacity);
    if (items)
    {
        v->items = items;
        v->capacity = capacity;
    }
}

void vector_add(struct vector *v, void *item)
{
    if (v->capacity == v->count)
        vector_resize(v, v->capacity * 2);
    v->items[v->count++] = item;
}

void vector_set(struct vector *v, int index, void *item)
{
    if (index >= 0 && index < v->count)
        v->items[index] = item;
}

void *vector_get(struct vector *v, int index)
{
    if (index >= 0 && index < v->count)
        return v->items[index];
    return NULL;
}

void vector_delete(struct vector *v, int index)
{
    if (index < 0 || index >= v->count)
        return;

    v->items[index] = NULL;

    for (int i = index; i < v->count - 1; i++)
    {
        v->items[i] = v->items[i + 1];
        v->items[i + 1] = NULL;
    }

    v->count--;

    if (v->count > 0 && v->count == v->capacity / 4)
        vector_resize(v, v->capacity / 2);
}

void vector_free(struct vector *v)
{
    free(v->items);
}