#include <stdlib.h>

#include <cmd.h>
#include <path_cmd.h>
#include <vector.h>

void path_cmd_init(struct path_cmd *c)
{
    init_command(&c->base, CMD_T_PATH_CMD, path_cmd_run);
}

void path_cmd_free(struct path_cmd *c)
{
    vector_free(c);
    free(c);
}

int path_cmd_run(struct cmd *c)
{
    struct path_cmd *path_cmd = (struct path_cmd *)c;
    return 0;
}