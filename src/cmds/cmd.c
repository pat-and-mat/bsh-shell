#include <cmds/cmd.h>
#include <stdio.h>
#include <stdbool.h>

void cmd_init_allocated(struct cmd *c, int type, bool (*run)(struct cmd *c))
{
    c->type = type;
    c->run = run;
}

int cmd_get_type(struct cmd *c)
{
    return c->type;
}

bool cmd_run(struct cmd *c)
{
    return (*c->run)(c);
}