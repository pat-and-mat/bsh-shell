#ifndef LEFT_CMD_H
#define LEFT_CMD_H

#include <cmds/redirect_cmd.h>

struct left_cmd
{
    struct redirect_cmd base;
};

struct left_cmd *left_cmd_init(char *filename);
void left_cmd_init_allocated(struct left_cmd *c, char *filename);

bool left_cmd_run(struct cmd *c);
void left_cmd_print(struct cmd *c);
void left_cmd_get_str(struct cmd *c, char *str);

#endif