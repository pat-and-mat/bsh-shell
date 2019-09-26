#ifndef PIPE_CMD_H
#define PIPE_CMD_H

#include <cmds/cmd.h>

struct pipe_cmd
{
    struct cmd base;
    struct cmd *left;
    struct cmd *right;
};

struct pipe_cmd *pipe_cmd_init();
void pipe_cmd_init_allocated(struct pipe_cmd *c);

struct cmd *pipe_cmd_get_left(struct pipe_cmd *c);
struct cmd *pipe_cmd_set_left(struct pipe_cmd *c, struct cmd *left);

struct cmd *pipe_cmd_get_right(struct pipe_cmd *c);
struct cmd *pipe_cmd_set_right(struct pipe_cmd *c, struct cmd *right);

bool pipe_cmd_run(struct cmd *c);

#endif