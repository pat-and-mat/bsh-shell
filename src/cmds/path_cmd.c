#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include <cmds/cmd.h>
#include <cmds/path_cmd.h>
#include <utils/vector.h>
#include <utils/xmemory.h>

struct path_cmd *path_cmd_init()
{
    struct path_cmd *path_cmd = xmalloc(sizeof(struct path_cmd));
    path_cmd_init_allocated(path_cmd);
    return path_cmd;
}

void path_cmd_init_allocated(struct path_cmd *c)
{
    cmd_init_allocated(&c->base, CMD_T_PATH_CMD, path_cmd_run, path_cmd_print);
    c->args = vector_init();
}

void path_cmd_add_arg(struct path_cmd *c, char *arg)
{
    vector_add(c->args, arg);
}

bool path_cmd_run(struct cmd *c)
{
    return true;
}

void path_cmd_print(struct cmd *c)
{
    struct path_cmd *path = (struct path_cmd *)c;

    if (vector_count(path->args) == 0)
        printf("<error>");
    else
        printf("%s", (char *)vector_get(path->args, 0));

    for (int i = 1; i < vector_count(path->args); i++)
        printf(" %s", (char *)vector_get(path->args, i));
}
