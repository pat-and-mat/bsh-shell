#ifndef RIGHT_APPEND_CMD_H
#define RIGHT_APPEND_CMD_H

#include <cmds/redirect_cmd.h>

struct right_append_cmd
{
    struct redirect_cmd base;
};

struct right_append_cmd *right_append_cmd_init(char *filename);
void right_append_cmd_init_allocated(struct right_append_cmd *c, char *filename);

bool right_append_cmd_run(struct cmd *c);
void right_append_cmd_print(struct cmd *c);

#endif