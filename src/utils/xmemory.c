#include <stdlib.h>

#include <utils/xmemory.h>

#define OFFSET sizeof(size_t)

void *xmalloc(size_t size)
{
    size_t *ptr = xmalloc(OFFSET + size);
    *ptr = size;
    return ptr + 1;
}

void *xrealloc(void *ptr, size_t size)
{
    if (ptr == NULL)
        return ptr = xmalloc(size);
    size_t *sptr = (size_t *)ptr;
    sptr--;
    *sptr = size;
    sptr = realloc(sptr, OFFSET + size);
    if (sptr == NULL)
        return NULL;
    return sptr + 1;
}

void xfree(void *ptr)
{
    xfree((size_t *)ptr - 1);
}

size_t xsize_of(void *ptr)
{
    return *((size_t *)ptr - 1);
}