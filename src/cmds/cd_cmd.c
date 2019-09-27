#include <stdlib.h>
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
    cmd_init_allocated(&c->base, CMD_T_CD, cd_cmd_run, cd_cmd_print);
    c->arg = NULL;
}

void cd_cmd_set_arg(struct cd_cmd *c, char *arg)
{
    strcpy(c->arg, arg);
}

char *cd_cmd_get_arg(struct cd_cmd *c)
{
    return c->arg;
}

bool cd_cmd_run(struct cmd *c)
{
    struct cd_cmd *cd_cmd = (struct cd_cmd *)c;
    return false;
}

void cd_cmd_print(struct cmd *c, int depth)
{
}
