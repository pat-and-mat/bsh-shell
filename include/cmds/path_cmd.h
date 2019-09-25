#ifndef PATH_CMD_H
#define PATH_CMD_H

#include <cmds/cmd.h>

struct vector;

struct path_cmd
{
    struct cmd base;
    struct vector *args;
};

void path_cmd_init(struct path_cmd *c);
void path_cmd_free(struct path_cmd *c);
struct path_cmd *path_cmd_copy(struct path_cmd *c);

void path_cmd_add_arg(struct path_cmd *c, char *arg);
int path_cmd_run(struct cmd *c);

#endif