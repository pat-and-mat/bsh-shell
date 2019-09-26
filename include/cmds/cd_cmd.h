#ifndef CD_CMD_H
#define CD_CMD_H

#include <cmds/cmd.h>

struct cd_cmd
{
    struct cmd base;
    struct cmd *left;
    struct cmd *right;
};

struct cd_cmd *cd_cmd_init();
void cd_cmd_init_allocated(struct cd_cmd *c);

struct cmd *cd_cmd_get_left(struct cd_cmd *c);
struct cmd *cd_cmd_set_left(struct cd_cmd *c, struct cmd *left);

struct cmd *cd_cmd_get_right(struct cd_cmd *c);
struct cmd *cd_cmd_set_right(struct cd_cmd *c, struct cmd *right);

int cd_cmd_run(struct cmd *c);

#endif