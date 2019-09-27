#ifndef PATH_CMD_H
#define PATH_CMD_H

#include <cmds/cmd.h>

struct vector;

struct path_cmd
{
    struct cmd base;
    struct vector *args;
};

struct path_cmd *path_cmd_init();
void path_cmd_init_allocated(struct path_cmd *c);
void path_cmd_add_arg(struct path_cmd *c, char *arg);
bool path_cmd_run(struct cmd *c);
void path_cmd_print(struct cmd *c);

#endif