#ifndef VECTOR_H
#define VECTOR_H

struct vector
{
    void **items;
    int capacity;
    int count;
};

void vector_init(struct vector *);
int vector_count(struct vector *);
static void vector_resize(struct vector *, int);
void vector_add(struct vector *, void *);
void vector_set(struct vector *, int, void *);
void *vector_get(struct vector *, int);
void vector_delete(struct vector *, int);

#endif