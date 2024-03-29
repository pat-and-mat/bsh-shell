#include <stdio.h>
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
    cmd_init_allocated(&c->base, CMD_T_SEP_CMD,
                       sep_cmd_run,
                       sep_cmd_run,
                       sep_cmd_print,
                       sep_cmd_get_str);
    c->left = NULL;
    c->right = NULL;
}

struct cmd *sep_cmd_get_left(struct sep_cmd *c)
{
    return c->left;
}

void sep_cmd_set_left(struct sep_cmd *c, struct cmd *left)
{
    c->left = left;
}

struct cmd *sep_cmd_get_right(struct sep_cmd *c)
{
    return c->right;
}

void sep_cmd_set_right(struct sep_cmd *c, struct cmd *right)
{
    c->right = right;
}

bool sep_cmd_run(struct cmd *c)
{
    struct sep_cmd *sep = (struct sep_cmd *)c;

    bool result = true;
    result = result && cmd_run_job(sep->left);
    result = result && (!sep->right || cmd_run_job(sep->right));

    return result;
}

void sep_cmd_print(struct cmd *c)
{
    struct sep_cmd *sep = (struct sep_cmd *)c;

    if (!sep->left)
        printf("<error>");
    else
        cmd_print(sep->left);

    printf(" ;");

    if (sep->right)
    {
        printf(" ");
        cmd_print(sep->right);
    }
}

void sep_cmd_get_str(struct cmd *c, char *str)
{
    struct sep_cmd *sep = (struct sep_cmd *)c;

    if (!sep->left)
        sprintf(str + strlen(str), "<error>");
    else
        cmd_get_str(sep->left, str + strlen(str));

    sprintf(str + strlen(str), " ;");

    if (sep->right)
    {
        sprintf(str + strlen(str), " ");
        cmd_get_str(sep->right, str + strlen(str));
    }
}
