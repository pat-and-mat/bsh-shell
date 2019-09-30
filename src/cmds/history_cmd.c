#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>

#include <cmds/cmd.h>
#include <cmds/history_cmd.h>
#include <utils/vector.h>
#include <utils/xmemory.h>

struct history_cmd *history_cmd_init()
{
    struct history_cmd *history_cmd = xmalloc(sizeof(struct history_cmd));
    history_cmd_init_allocated(history_cmd);
    return history_cmd;
}

void history_cmd_init_allocated(struct history_cmd *c)
{
    simple_cmd_init_allocated(&c->base, "history");
    cmd_init_allocated((struct cmd *)(&c->base), CMD_T_CD, history_cmd_run, history_cmd_print);
}

bool history_cmd_run(struct cmd *c)
{
    return true;
}

void history_cmd_print(struct cmd *c)
{
    simple_cmd_print(c);
}
