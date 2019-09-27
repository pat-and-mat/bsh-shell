#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include <cmds/cmd.h>
#include <cmds/left_cmd.h>
#include <utils/vector.h>
#include <utils/xmemory.h>

struct left_cmd *left_cmd_init()
{
    struct left_cmd *left_cmd = xmalloc(sizeof(struct left_cmd));
    left_cmd_init_allocated(left_cmd);
    return left_cmd;
}

void left_cmd_init_allocated(struct left_cmd *c)
{
    cmd_init_allocated(&c->base, CMD_T_LEFT_CMD, left_cmd_run, left_cmd_print);
    c->cmd = NULL;
    c->filename = NULL;
}

struct cmd *left_cmd_get_cmd(struct left_cmd *c)
{
    return c->cmd;
}
void left_cmd_set_cmd(struct left_cmd *c, struct cmd *cmd)
{
    c->cmd = cmd;
}

char *left_cmd_get_filename(struct left_cmd *c)
{
    return c->filename;
}

void left_cmd_set_filename(struct left_cmd *c, char *filename)
{
    c->filename = filename;
}

bool left_cmd_run(struct cmd *c)
{
    struct left_cmd *left = (struct left_cmd *)c;

    if (!left->cmd || !cmd_run(left->cmd))
        printf("<error>");

    printf(" < ");

    if (!left->filename)
        printf("<error>");
    else
        printf("%s", left->filename);

    return true;
}

void left_cmd_print(struct cmd *c, int depth)
{
}
