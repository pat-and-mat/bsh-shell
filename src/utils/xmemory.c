#include <stdlib.h>
#include <string.h>

#include <utils/xmemory.h>

#define OFFSET sizeof(size_t)

void *xmalloc(size_t size)
{
    size_t *ptr = malloc(OFFSET + size);
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
    free((size_t *)ptr - 1);
}

void *xcopy(void *ptr)
{
    size_t item_size = xsize_of(ptr);
    void *item_cpy = xmalloc(item_size);
    memcpy(item_cpy, ptr, item_size);
    return item_cpy;
}

void *xcopy_with_size(void *ptr, size_t item_size)
{
    void *item_cpy = xmalloc(item_size);
    memcpy(item_cpy, ptr, item_size);
    return item_cpy;
}

size_t xsize_of(void *ptr)
{
    return *((size_t *)ptr - 1);
}

char *xstring(char *s)
{
    return xcopy_with_size(s, sizeof(char) * (strlen(s) + 1));
}
