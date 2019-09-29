#include <cmds/cmd.h>
#include <stdio.h>
#include <stdbool.h>

void cmd_init_allocated(struct cmd *c, int type, bool (*run)(struct cmd *c), void (*print)(struct cmd *c))
{
    c->type = type;
    c->run = run;
    c->print = print;
}

int cmd_get_type(struct cmd *c)
{
    return c->type;
}

bool cmd_run(struct cmd *c)
{
    return (*c->run)(c);
}

void cmd_print(struct cmd *c)
{
    (*c->print)(c);
}