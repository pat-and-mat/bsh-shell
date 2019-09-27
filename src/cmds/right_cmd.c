#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include <cmds/cmd.h>
#include <cmds/right_cmd.h>
#include <utils/vector.h>
#include <utils/xmemory.h>

struct right_cmd *right_cmd_init()
{
    struct right_cmd *right_cmd = xmalloc(sizeof(struct right_cmd));
    right_cmd_init_allocated(right_cmd);
    return right_cmd;
}

void right_cmd_init_allocated(struct right_cmd *c)
{
    cmd_init_allocated(&c->base, CMD_T_RIGHT_CMD, right_cmd_run);
    c->cmd = NULL;
    c->filename = NULL;
}

struct cmd *right_cmd_get_cmd(struct right_cmd *c)
{
    return c->cmd;
}

void right_cmd_set_cmd(struct right_cmd *c, struct cmd *cmd)
{
    c->cmd = cmd;
}

char *right_cmd_get_filename(struct right_cmd *c)
{
    return c->filename;
}

void right_cmd_set_filename(struct right_cmd *c, char *filename)
{
    c->filename = filename;
}

bool right_cmd_run(struct cmd *c)
{
    struct right_cmd *right_cmd = (struct right_cmd *)c;
    return false;
}