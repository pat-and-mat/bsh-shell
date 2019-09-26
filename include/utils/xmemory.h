#ifndef XMEMORY_H
#define XMEMORY_H

#include <stddef.h>

void xmem_init();
void xmem_free();
void *xmalloc(size_t size);
void *xrealloc(void *ptr, size_t size);

#endif