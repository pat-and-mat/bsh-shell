#include <stdlib.h>
#include <utils/xmemory.h>

#define XMEM_INIT_CAPACITY 10

struct xmemory
{
    int count;
    int capacity;
    void **addrs;
};

struct xmemory xmemory;

void xmem_resize();

void xmem_init()
{
    xmemory.capacity = XMEM_INIT_CAPACITY;
    xmemory.count = 0;
    xmemory.addrs = malloc(sizeof(void *) * XMEM_INIT_CAPACITY);
}

void xmem_free()
{
    for (int i = 0; i < xmemory.count; i++)
        free(xmemory.addrs[i]);
    free(xmemory.addrs);
}

void *xmalloc(size_t size)
{
    if (xmemory.capacity == xmemory.count)
        xmem_resize();
    return xmemory.addrs[xmemory.count++] = malloc(size);
}

void *xrealloc(void *ptr, size_t size)
{
    void *new_ptr = realloc(ptr, size);
    if (new_ptr)
        for (int i = 0; i < xmemory.count; i++)
            if (xmemory.addrs[i] == ptr)
                xmemory.addrs[i] = new_ptr;

    return new_ptr;
}

void xmem_resize()
{
    int capacity = xmemory.capacity * 2;
    void **addrs = realloc(xmemory.addrs, sizeof(void *) * capacity);
    if (addrs)
    {
        xmemory.addrs = addrs;
        xmemory.capacity = capacity;
    }
}