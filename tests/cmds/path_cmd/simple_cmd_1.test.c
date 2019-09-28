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

    struct simple_cmd *p = simple_cmd_init("arg1");

    char *arg1 = "arg1";
    simple_cmd_add_arg(p, arg1);

    if (!strcmp("arg1", vector_get(p->args, 0)))
    {
        xmem_free();
        return 0;
    }

    xmem_free();
    return -1;
}