#ifndef RIGHT_APPEND_CMD_H
#define RIGHT_APPEND_CMD_H

#include <cmds/cmd.h>

struct right_append_cmd
{
    struct cmd base;
    struct cmd *left;
    struct cmd *right;
};

struct right_append_cmd *right_append_cmd_init();
void right_append_cmd_init_allocated(struct right_append_cmd *c);

struct cmd *right_append_cmd_get_left(struct right_append_cmd *c);
struct cmd *right_append_cmd_set_left(struct right_append_cmd *c, struct cmd *left);

struct cmd *right_append_cmd_get_right(struct right_append_cmd *c);
struct cmd *right_append_cmd_set_right(struct right_append_cmd *c, struct cmd *right);

int right_append_cmd_run(struct cmd *c);

#endif