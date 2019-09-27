#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include <cmds/cmd.h>
#include <cmds/right_append_cmd.h>
#include <utils/vector.h>
#include <utils/xmemory.h>

struct right_append_cmd *right_append_cmd_init()
{
    struct right_append_cmd *right_append_cmd = xmalloc(sizeof(struct right_append_cmd));
    right_append_cmd_init_allocated(right_append_cmd);
    return right_append_cmd;
}

void right_append_cmd_init_allocated(struct right_append_cmd *c)
{
    cmd_init_allocated(&c->base, CMD_T_RIGHT_APPEND_CMD, right_append_cmd_run);
    c->cmd = NULL;
    c->filename = NULL;
}

struct cmd *right_append_cmd_get_cmd(struct right_append_cmd *c)
{
    return c->cmd;
}
void right_append_cmd_set_cmd(struct right_append_cmd *c, struct cmd *cmd)
{
    c->cmd = cmd;
}

char *right_append_cmd_get_filename(struct right_append_cmd *c)
{
    return c->filename;
}

void right_append_cmd_set_filename(struct right_append_cmd *c, char *filename)
{
    c->filename = filename;
}

bool right_append_cmd_run(struct cmd *c)
{
    struct right_append_cmd *right_append_cmd = (struct right_append_cmd *)c;
    return false;
}