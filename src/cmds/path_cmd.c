#include <stdlib.h>
#include <string.h>

#include <cmds/cmd.h>
#include <cmds/path_cmd.h>
#include <utils/vector.h>

void path_cmd_init(struct path_cmd *c)
{
    cmd_init(&c->base, CMD_T_PATH_CMD, path_cmd_run);
    c->args = malloc(sizeof(struct vector));
    vector_init(c->args, NULL);
}

void path_cmd_free(struct path_cmd *c)
{
    vector_free(c->args);
    free(c->args);
}

void path_cmd_add_arg(struct path_cmd *c, char *arg)
{
    vector_add(c->args, arg, sizeof(char) * (strlen(arg) + 1));
}

int path_cmd_run(struct cmd *c)
{
    struct path_cmd *path_cmd = (struct path_cmd *)c;
    return 0;
}