#ifndef RIGHT_APPEND_CMD_H
#define RIGHT_APPEND_CMD_H

#include <cmds/cmd.h>

struct right_append_cmd
{
    struct cmd base;
    char *filename;
};

struct right_append_cmd *right_append_cmd_init(char *filename);
void right_append_cmd_init_allocated(struct right_append_cmd *c, char *filename);

bool right_append_cmd_run(struct cmd *c);
void right_append_cmd_print(struct cmd *c);

#endif