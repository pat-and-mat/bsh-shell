#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include <cmds/cmd.h>
#include <cmds/right_append_cmd.h>
#include <utils/vector.h>
#include <utils/xmemory.h>

struct right_append_cmd *right_append_cmd_init()
{
    struct right_append_cmd *right_append_cmd = xmalloc(sizeof(struct right_append_cmd));
    right_append_cmd_init_allocated(right_append_cmd);
    return right_append_cmd;
}

void right_append_cmd_init_allocated(struct right_append_cmd *c)
{
    cmd_init_allocated(&c->base, CMD_T_RIGHT_APPEND_CMD, right_append_cmd_run);
}

struct cmd *right_append_cmd_get_left(struct right_append_cmd *c)
{
    return c->left;
}
struct cmd *right_append_cmd_set_left(struct right_append_cmd *c, struct cmd *left)
{
    c->left = left;
    return c->left;
}

struct cmd *right_append_cmd_get_right(struct right_append_cmd *c)
{
    return c->right;
}

struct cmd *right_append_cmd_set_right(struct right_append_cmd *c, struct cmd *right)
{
    c->right = right;
    return c->right;
}

bool right_append_cmd_run(struct cmd *c)
{
    struct right_append_cmd *right_append_cmd = (struct right_append_cmd *)c;
    return false;
}