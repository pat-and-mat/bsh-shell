#ifndef RIGHT_CMD_H
#define RIGHT_CMD_H

#include <cmds/cmd.h>

struct right_cmd
{
    struct cmd base;
    struct cmd *left;
    struct cmd *right;
};

struct right_cmd *right_cmd_init();
void right_cmd_init_allocated(struct right_cmd *c);

struct cmd *right_cmd_get_left(struct right_cmd *c);
struct cmd *right_cmd_set_left(struct right_cmd *c, struct cmd *left);

struct cmd *right_cmd_get_right(struct right_cmd *c);
struct cmd *right_cmd_set_right(struct right_cmd *c, struct cmd *right);

bool right_cmd_run(struct cmd *c);

#endif