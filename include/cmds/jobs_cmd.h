#ifndef JOBS_CMD_H
#define JOBS_CMD_H

#include <cmds/simple_cmd.h>

struct jobs_cmd
{
    struct simple_cmd base;
};

struct jobs_cmd *jobs_cmd_init();
void jobs_cmd_init_allocated(struct jobs_cmd *c);

bool jobs_cmd_run(struct cmd *c);
void jobs_cmd_print(struct cmd *c);
void jobs_cmd_get_str(struct cmd *c, char *str);

#endif