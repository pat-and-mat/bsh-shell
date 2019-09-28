#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include <cmds/cmd.h>
#include <cmds/cd_cmd.h>
#include <utils/vector.h>
#include <utils/xmemory.h>

struct cd_cmd *cd_cmd_init()
{
    struct cd_cmd *cd_cmd = xmalloc(sizeof(struct cd_cmd));
    cd_cmd_init_allocated(cd_cmd);
    return cd_cmd;
}

void cd_cmd_init_allocated(struct cd_cmd *c)
{
    simple_cmd_init_allocated(&c->base, "cd");
    cmd_init_allocated((struct cmd *)(&c->base), CMD_T_CD, cd_cmd_run, cd_cmd_print);
}

bool cd_cmd_run(struct cmd *c)
{
    return true;
}

void cd_cmd_print(struct cmd *c)
{
    simple_cmd_print(c);
}
