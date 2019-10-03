#ifndef SEP_CMD_H
#define SEP_CMD_H

#include <cmds/cmd.h>

struct sep_cmd
{
    struct cmd base;
    struct cmd *left;
    struct cmd *right;
};

struct sep_cmd *sep_cmd_init();
void sep_cmd_init_allocated(struct sep_cmd *c);

struct cmd *sep_cmd_get_left(struct sep_cmd *c);
void sep_cmd_set_left(struct sep_cmd *c, struct cmd *left);

struct cmd *sep_cmd_get_right(struct sep_cmd *c);
void sep_cmd_set_right(struct sep_cmd *c, struct cmd *right);

bool sep_cmd_run(struct cmd *c);
void sep_cmd_print(struct cmd *c);

#endif