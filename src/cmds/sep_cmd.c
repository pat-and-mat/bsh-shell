#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include <cmds/cmd.h>
#include <cmds/sep_cmd.h>
#include <utils/vector.h>
#include <utils/xmemory.h>

struct sep_cmd *sep_cmd_init()
{
    struct sep_cmd *sep_cmd = xmalloc(sizeof(struct sep_cmd));
    sep_cmd_init_allocated(sep_cmd);
    return sep_cmd;
}

void sep_cmd_init_allocated(struct sep_cmd *c)
{
    cmd_init_allocated(&c->base, CMD_T_SEP_CMD, sep_cmd_run);
}

struct cmd *sep_cmd_get_left(struct sep_cmd *c)
{
    return c->left;
}
struct cmd *sep_cmd_set_left(struct sep_cmd *c, struct cmd *left)
{
    c->left = left;
    return c->left;
}

struct cmd *sep_cmd_get_right(struct sep_cmd *c)
{
    return c->right;
}

struct cmd *sep_cmd_set_right(struct sep_cmd *c, struct cmd *right)
{
    c->right = right;
    return c->right;
}

bool sep_cmd_run(struct cmd *c)
{
    struct sep_cmd *sep_cmd = (struct sep_cmd *)c;
    return false;
}