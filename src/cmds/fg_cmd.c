#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>

#include <cmds/cmd.h>
#include <cmds/fg_cmd.h>
#include <utils/vector.h>
#include <utils/xmemory.h>

struct fg_cmd *fg_cmd_init()
{
    struct fg_cmd *fg_cmd = xmalloc(sizeof(struct fg_cmd));
    fg_cmd_init_allocated(fg_cmd);
    return fg_cmd;
}

void fg_cmd_init_allocated(struct fg_cmd *c)
{
    simple_cmd_init_allocated(&c->base, "fg");
    cmd_init_allocated((struct cmd *)(&c->base), CMD_T_CD, fg_cmd_run, fg_cmd_print);
}

bool fg_cmd_run(struct cmd *c)
{
    struct fg_cmd *fg = (struct fg_cmd *)c;

    int saved_stdout = dup(STDOUT_FILENO);

    if (!simple_cmd_open_redirects(c))
    {
        simple_cmd_close_redirects(c);
        return false;
    }

    if (true)
    {
        simple_cmd_close_redirects(c);
        return true;
    }

    simple_cmd_close_redirects(c);
    return false;
}

void fg_cmd_print(struct cmd *c)
{
    simple_cmd_print(c);
}
