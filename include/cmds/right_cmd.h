#ifndef RIGHT_CMD_H
#define RIGHT_CMD_H

#include <cmds/cmd.h>

struct right_cmd
{
    struct cmd base;
    char *filename;
};

struct right_cmd *right_cmd_init(char *filename);
void right_cmd_init_allocated(struct right_cmd *c, char *filename);

bool right_cmd_run(struct cmd *c);
void right_cmd_print(struct cmd *c);

#endif