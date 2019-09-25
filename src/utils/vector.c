#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <utils/xmemory.h>
#include <utils/vector.h>

#define VECTOR_INIT_CAPACITY 5

void vector_init(struct vector *v)
{
    v->capacity = VECTOR_INIT_CAPACITY;
    v->count = 0;
    v->items = xmalloc(sizeof(void *) * v->capacity);
}

int vector_count(struct vector *v)
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
    size_t item_size = xsize_of(item);
    void *item_cpy = xmalloc(item_size);
    memcpy(item_cpy, item, item_size);
    v->items[v->count++] = item_cpy;
}

void vector_set(struct vector *v, int index, void *item)
{
    if (index >= 0 && index < v->count)
    {
        xfree(v->items[index]);
        v->items[index] = item;
    }
    size_t item_size = xsize_of(item);
    void *item_cpy = xmalloc(item_size);
    memcpy(item_cpy, item, item_size);
    v->items[index] = item_cpy;
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

    xfree(v->items[index]);
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
    for (int i = 0; i < v->count; i++)
    {
        xfree(v->items[i]);
        v->items[i] = NULL;
    }
    xfree(v->items);
}