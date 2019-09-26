#include <cmds/cmd.h>
#include <stdio.h>

void cmd_init_allocated(struct cmd *c, int type, int (*run)(struct cmd *c))
{
    c->type = type;
    c->run = run;
}

int cmd_get_type(struct cmd *c)
{
    return c->type;
}

int cmd_run(struct cmd *c)
{
    if (c->run != NULL)
        return (*c->run)(c);
    return -1;
}