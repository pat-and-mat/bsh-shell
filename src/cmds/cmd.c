#include <cmd.h>

void init_cmd(struct cmd *c, int type, int (*run)(struct cmd *c))
{
    c->type = type;
    c->run = run;
}