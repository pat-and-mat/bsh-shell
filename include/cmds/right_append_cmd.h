#ifndef RIGHT_APPEND_CMD_H
#define RIGHT_APPEND_CMD_H

#include <cmds/cmd.h>

struct right_append_cmd
{
    struct cmd base;
    struct cmd *cmd;
    char *filename;
};

struct right_append_cmd *right_append_cmd_init();
void right_append_cmd_init_allocated(struct right_append_cmd *c);

struct cmd *right_append_cmd_get_cmd(struct right_append_cmd *c);
void right_append_cmd_set_cmd(struct right_append_cmd *c, struct cmd *cmd);

char *right_append_cmd_get_filename(struct right_append_cmd *c);
void right_append_cmd_set_filename(struct right_append_cmd *c, char *filename);

bool right_append_cmd_run(struct cmd *c);
void right_append_cmd_print(struct cmd *c);

#endif