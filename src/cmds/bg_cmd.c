#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>

#include <cmds/cmd.h>
#include <cmds/bg_cmd.h>
#include <utils/vector.h>
#include <utils/xmemory.h>
#include <shell/jobs.h>

struct bg_cmd *bg_cmd_init()
{
    struct bg_cmd *bg_cmd = xmalloc(sizeof(struct bg_cmd));
    bg_cmd_init_allocated(bg_cmd);
    return bg_cmd;
}

void bg_cmd_init_allocated(struct bg_cmd *c)
{
    cmd_init_allocated(&c->base, CMD_T_BG_CMD,
                       bg_cmd_run,
                       bg_cmd_run,
                       bg_cmd_print);
    c->left = NULL;
    c->right = NULL;
}

struct cmd *bg_cmd_get_left(struct bg_cmd *c)
{
    return c->left;
}

void bg_cmd_set_left(struct bg_cmd *c, struct cmd *left)
{
    c->left = left;
}

struct cmd *bg_cmd_get_right(struct bg_cmd *c)
{
    return c->right;
}

void bg_cmd_set_right(struct bg_cmd *c, struct cmd *right)
{
    c->right = right;
}

bool bg_cmd_run(struct cmd *c)
{
    struct bg_cmd *bg = (struct bg_cmd *)c;

    bool result = true;
    result = result && jobs_run_bg(bg->left);
    result = result && (!bg->right || cmd_run_job(bg->right));

    return result;
}

void bg_cmd_print(struct cmd *c)
{
    struct bg_cmd *bg = (struct bg_cmd *)c;

    if (!bg->left)
        printf("<error>");
    else
        cmd_print(bg->left);

    printf(" &");

    if (bg->right)
    {
        printf(" ");
        cmd_print(bg->right);
    }
}
