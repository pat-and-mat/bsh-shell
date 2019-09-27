#ifndef RIGHT_CMD_H
#define RIGHT_CMD_H

#include <cmds/cmd.h>

struct right_cmd
{
    struct cmd base;
    struct cmd *cmd;
    char *filename;
};

struct right_cmd *right_cmd_init();
void right_cmd_init_allocated(struct right_cmd *c);

struct cmd *right_cmd_get_cmd(struct right_cmd *c);
void right_cmd_set_cmd(struct right_cmd *c, struct cmd *cmd);

char *right_cmd_get_filename(struct right_cmd *c);
void right_cmd_set_filename(struct right_cmd *c, char *filename);

int right_cmd_run(struct cmd *c);

#endif