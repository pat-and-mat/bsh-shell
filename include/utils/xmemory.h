#ifndef XMEMORY_H
#define XMEMORY_H

#include <stddef.h>

void *xmalloc(size_t size);
void *xrealloc(void *ptr, size_t size);
void xfree(void *ptr);
void *xcopy(void *ptr);
void *xcopy_with_size(void *ptr, size_t size);
size_t xsize_of(void *ptr);
char *xstring(char *);

#endif