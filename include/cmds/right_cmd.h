#ifndef RIGHT_CMD_H
#define RIGHT_CMD_H

#include <cmds/redirect_cmd.h>

struct right_cmd
{
    struct redirect_cmd base;
};

struct right_cmd *right_cmd_init(char *filename);
void right_cmd_init_allocated(struct right_cmd *c, char *filename);

bool right_cmd_run(struct cmd *c, bool is_root);
void right_cmd_print(struct cmd *c);

#endif