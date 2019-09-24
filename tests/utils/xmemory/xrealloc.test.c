#include <utils/xmemory.h>

struct test_struct
{
    int a;
    int b;
};

struct test_struct_1
{
    struct test_struct base;
    int a;
    int b;
};

int main()
{
    struct test_struct *ts = xmalloc(sizeof(struct test_struct));
    ts->a = 25;
    ts->b = 30;

    struct test_struct_1 *ts1 = xrealloc(ts, sizeof(struct test_struct_1));
    ts1->a = 45;
    ts1->b = 90;

    if (ts1->base.a != 25 || ts1->base.b != 30)
        return -1;

    xfree(ts1);
    return 0;
}