#ifndef HISTORY_CMD_H
#define HISTORY_CMD_H

#include <cmds/simple_cmd.h>

struct history_cmd
{
    struct simple_cmd base;
};

struct history_cmd *history_cmd_init();
void history_cmd_init_allocated(struct history_cmd *c);

bool history_cmd_run(struct cmd *c);
void history_cmd_print(struct cmd *c);

#endif