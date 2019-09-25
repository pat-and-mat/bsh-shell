#include <stdlib.h>
#include <string.h>

#include <cmds/cmd.h>
#include <cmds/path_cmd.h>
#include <utils/vector.h>
#include <utils/strutils.h>

void path_cmd_init(struct path_cmd *c)
{
    cmd_init(&c->base, CMD_T_PATH_CMD, path_cmd_run);
    c->args = malloc(sizeof(struct vector));
    vector_init(c->args, NULL, (void *(*)(void *))str_copy);
}

void path_cmd_free(struct path_cmd *c)
{
    vector_free(c->args);
    free(c->args);
}

struct path_cmd *path_cmd_copy(struct path_cmd *c)
{
    struct path_cmd *cpy = malloc(sizeof(struct path_cmd));
    cmd_init(&cpy->base, CMD_T_PATH_CMD, path_cmd_run);
    c->args = vector_copy(c->args);
}

void path_cmd_add_arg(struct path_cmd *c, char *arg)
{
    vector_add(c->args, arg);
}

int path_cmd_run(struct cmd *c)
{
    struct path_cmd *path_cmd = (struct path_cmd *)c;
    return 0;
}