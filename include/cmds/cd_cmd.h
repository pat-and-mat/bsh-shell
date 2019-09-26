#ifndef CD_CMD_H
#define CD_CMD_H

#include <cmds/cmd.h>

struct cd_cmd
{
    struct cmd base;
    char *arg;
};

struct cd_cmd *cd_cmd_init();
void cd_cmd_init_allocated(struct cd_cmd *c);

struct cmd *cd_cmd_get_arg(struct cd_cmd *c);
struct cmd *cd_cmd_set_arg(struct cd_cmd *c, char *arg);

bool cd_cmd_run(struct cmd *c);

#endif