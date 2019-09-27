#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include <cmds/cmd.h>
#include <cmds/right_cmd.h>
#include <utils/vector.h>
#include <utils/xmemory.h>

struct right_cmd *right_cmd_init()
{
    struct right_cmd *right_cmd = xmalloc(sizeof(struct right_cmd));
    right_cmd_init_allocated(right_cmd);
    return right_cmd;
}

void right_cmd_init_allocated(struct right_cmd *c)
{
    cmd_init_allocated(&c->base, CMD_T_RIGHT_CMD, right_cmd_run);
}

struct cmd *right_cmd_get_left(struct right_cmd *c)
{
    return c->left;
}
struct cmd *right_cmd_set_left(struct right_cmd *c, struct cmd *left)
{
    c->left = left;
    return c->left;
}

struct cmd *right_cmd_get_right(struct right_cmd *c)
{
    return c->right;
}

struct cmd *right_cmd_set_right(struct right_cmd *c, struct cmd *right)
{
    c->right = right;
    return c->right;
}

bool right_cmd_run(struct cmd *c)
{
    struct right_cmd *right_cmd = (struct right_cmd *)c;
    return false;
}