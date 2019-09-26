#ifndef BG_CMD_H
#define BG_CMD_H

#include <cmds/cmd.h>

struct bg_cmd
{
    struct cmd base;
    struct cmd *left;
    struct cmd *right;
};

struct bg_cmd *bg_cmd_init();
void bg_cmd_init_allocated(struct bg_cmd *c);

struct cmd *bg_cmd_get_left(struct bg_cmd *c);
struct cmd *bg_cmd_set_left(struct bg_cmd *c, struct cmd *left);

struct cmd *bg_cmd_get_right(struct bg_cmd *c);
struct cmd *bg_cmd_set_right(struct bg_cmd *c, struct cmd *right);

bool bg_cmd_run(struct cmd *c);

#endif