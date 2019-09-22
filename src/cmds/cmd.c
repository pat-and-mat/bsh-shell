#include <cmds/cmd.h>

void cmd_init(struct cmd *c, int type, int (*run)(struct cmd *c))
{
    c->type = type;
    c->run = run;
}