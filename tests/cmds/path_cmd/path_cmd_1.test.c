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

    char *arg1 = "arg1";
    path_cmd_add_arg(&p, arg1);

    if (!strcmp("arg1", vector_get(p.args, 0)))
    {
        xmem_free();
        return 0;
    }

    xmem_free();
    return -1;
}