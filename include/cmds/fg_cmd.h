#ifndef FG_CMD_H
#define FG_CMD_H

#include <cmds/simple_cmd.h>

struct fg_cmd
{
    struct simple_cmd base;
};

struct fg_cmd *fg_cmd_init();
void fg_cmd_init_allocated(struct fg_cmd *c);

bool fg_cmd_run(struct cmd *c);
void fg_cmd_print(struct cmd *c);
void fg_cmd_get_str(struct cmd *c, char *str);

#endif