#ifndef LEFT_CMD_H
#define LEFT_CMD_H

#include <cmds/cmd.h>

struct left_cmd
{
    struct cmd base;
    struct cmd *left;
    struct cmd *right;
};

struct left_cmd *left_cmd_init();
void left_cmd_init_allocated(struct left_cmd *c);

struct cmd *left_cmd_get_left(struct left_cmd *c);
struct cmd *left_cmd_set_left(struct left_cmd *c, struct cmd *left);

struct cmd *left_cmd_get_right(struct left_cmd *c);
struct cmd *left_cmd_set_right(struct left_cmd *c, struct cmd *right);

int left_cmd_run(struct cmd *c);

#endif