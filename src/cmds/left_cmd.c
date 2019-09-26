#include <stdlib.h>
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
    cmd_init_allocated(&c->base, CMD_T_LEFT_CMD, left_cmd_run);
}

struct cmd *left_cmd_get_left(struct left_cmd *c)
{
    return c->left;
}
struct cmd *left_cmd_set_left(struct left_cmd *c, struct cmd *left)
{
    c->left = left;
    return c->left;
}

struct cmd *left_cmd_get_right(struct left_cmd *c)
{
    return c->right;
}

struct cmd *left_cmd_set_right(struct left_cmd *c, struct cmd *right)
{
    c->right = right;
    return c->right;
}

bool left_cmd_run(struct cmd *c)
{
    struct left_cmd *left_cmd = (struct left_cmd *)c;
    return false;
}