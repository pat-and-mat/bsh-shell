#ifndef CD_CMD_H
#define CD_CMD_H

#include <cmds/simple_cmd.h>

struct cd_cmd
{
    struct simple_cmd base;
};

struct cd_cmd *cd_cmd_init();
void cd_cmd_init_allocated(struct cd_cmd *c);

bool cd_cmd_run(struct cmd *c);
void cd_cmd_print(struct cmd *c);

#endif