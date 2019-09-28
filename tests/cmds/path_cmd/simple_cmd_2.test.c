#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <cmds/cmd.h>
#include <cmds/simple_cmd.h>
#include <utils/vector.h>
#include <utils/xmemory.h>

int main()
{
    xmem_init();

    struct simple_cmd *p = simple_cmd_init("agr1");

    char *arg1 = "agr1";
    simple_cmd_add_arg(p, arg1);

    char *arg2 = "agr2";
    simple_cmd_add_arg(p, arg2);

    char *arg3 = "agr3";
    simple_cmd_add_arg(p, arg3);

    char *arg4 = "agr4";
    simple_cmd_add_arg(p, arg4);

    char *arg5 = "agr5";
    simple_cmd_add_arg(p, arg5);

    if (5 == vector_count(p->args))
    {
        xmem_free();
        return 0;
    }

    xmem_free();
    return -1;
}