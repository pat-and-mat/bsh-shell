#ifndef VECTOR_H
#define VECTOR_H

struct vector
{
    void **items;
    int capacity;
    int count;
    void (*free_item)(void *item);
    void *(*copy_item)(void *item);
};

void vector_init(struct vector *v, void (*)(void *), void *(*)(void *));
struct vector *vector_copy(struct vector *);

int vector_count(struct vector *);
static void vector_resize(struct vector *, int);
void vector_add(struct vector *, void *);
void vector_set(struct vector *, int, void *);
void *vector_get(struct vector *, int);
void vector_delete(struct vector *, int);
void vector_free(struct vector *);

#endif