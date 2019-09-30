#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include <cmds/cmd.h>
#include <cmds/right_cmd.h>
#include <utils/vector.h>
#include <utils/xmemory.h>

struct right_cmd *right_cmd_init(char *filename)
{
    struct right_cmd *right_cmd = xmalloc(sizeof(struct right_cmd));
    right_cmd_init_allocated(right_cmd, filename);
    return right_cmd;
}

void right_cmd_init_allocated(struct right_cmd *c, char *filename)
{
    redirect_cmd_init_allocated(&c->base, filename);
    cmd_init_allocated((struct cmd *)&c->base, CMD_T_LEFT_CMD, right_cmd_run, right_cmd_print);
}

bool right_cmd_run(struct cmd *c)
{
    return true;
}

void right_cmd_print(struct cmd *c)
{
    struct right_cmd *right = (struct right_cmd *)c;

    printf("> ");

    if (!right->base.filename)
        printf("<error>");
    else
        printf("%s", right->base.filename);
}
