#ifndef XMEMORY_H
#define XMEMORY_H

#include <stddef.h>

void *xmalloc(size_t size);
void *xrealloc(void *ptr, size_t size);
void xfree(void *ptr);
size_t xsize_of(void *ptr);

#endif