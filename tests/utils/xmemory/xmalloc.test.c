#include <utils/xmemory.h>

struct test_struct
{
    int a;
    int b;
};

int main()
{
    struct test_struct *ts = xmalloc(sizeof(struct test_struct));
    ts->a = 25;
    ts->b = 30;

    if (xsize_of(ts) != sizeof(struct test_struct))
        return -1;
    xfree(ts);
    return 0;
}