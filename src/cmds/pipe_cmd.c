#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include <cmds/cmd.h>
#include <cmds/pipe_cmd.h>
#include <utils/vector.h>
#include <utils/xmemory.h>

struct pipe_cmd *pipe_cmd_init()
{
    struct pipe_cmd *pipe_cmd = xmalloc(sizeof(struct pipe_cmd));
    pipe_cmd_init_allocated(pipe_cmd);
    return pipe_cmd;
}

void pipe_cmd_init_allocated(struct pipe_cmd *c)
{
    cmd_init_allocated(&c->base, CMD_T_PIPE_CMD, pipe_cmd_run, pipe_cmd_print);
    c->left = NULL;
    c->right = NULL;
}

struct cmd *pipe_cmd_get_left(struct pipe_cmd *c)
{
    return c->left;
}
void pipe_cmd_set_left(struct pipe_cmd *c, struct cmd *left)
{
    c->left = left;
}

struct cmd *pipe_cmd_get_right(struct pipe_cmd *c)
{
    return c->right;
}

void pipe_cmd_set_right(struct pipe_cmd *c, struct cmd *right)
{
    c->right = right;
}

bool pipe_cmd_run(struct cmd *c)
{
    struct pipe_cmd *pipe_cmd = (struct pipe_cmd *)c;
    return false;
}

void pipe_cmd_print(struct cmd *c, int depth)
{
}