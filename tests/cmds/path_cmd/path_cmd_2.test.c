#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <cmds/cmd.h>
#include <cmds/path_cmd.h>
#include <utils/vector.h>
#include <utils/xmemory.h>

int main()
{
    xmem_init();

    struct path_cmd p;
    path_cmd_init(&p);

    char *arg1 = "agr1";
    path_cmd_add_arg(&p, arg1);

    char *arg2 = "agr2";
    path_cmd_add_arg(&p, arg2);

    char *arg3 = "agr3";
    path_cmd_add_arg(&p, arg3);

    char *arg4 = "agr4";
    path_cmd_add_arg(&p, arg4);

    char *arg5 = "agr5";
    path_cmd_add_arg(&p, arg5);

    if (5 == vector_count(p.args))
    {
        xmem_free();
        return 0;
    }

    xmem_free();
    return -1;
}