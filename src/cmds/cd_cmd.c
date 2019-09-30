#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>

#include <cmds/cmd.h>
#include <cmds/cd_cmd.h>
#include <utils/vector.h>
#include <utils/xmemory.h>

struct cd_cmd *cd_cmd_init()
{
    struct cd_cmd *cd_cmd = xmalloc(sizeof(struct cd_cmd));
    cd_cmd_init_allocated(cd_cmd);
    return cd_cmd;
}

void cd_cmd_init_allocated(struct cd_cmd *c)
{
    simple_cmd_init_allocated(&c->base, "cd");
    cmd_init_allocated((struct cmd *)(&c->base), CMD_T_CD, cd_cmd_run, cd_cmd_print);
}

bool cd_cmd_run(struct cmd *c)
{
    struct cd_cmd *cd = (struct cd_cmd *)c;

    int saved_stdout = dup(STDOUT_FILENO);

    if (!simple_cmd_open_redirects(c))
    {
        simple_cmd_close_redirects(c);
        return false;
    }

    if ((vector_count(cd->base.args) == 1 && chdir(getpwuid(getuid())->pw_dir) == 0) ||
        (vector_count(cd->base.args) == 2 && chdir(vector_get(cd->base.args, 1)) == 0))
    {
        simple_cmd_close_redirects(c);
        return true;
    }

    simple_cmd_close_redirects(c);
    return false;
}

void cd_cmd_print(struct cmd *c)
{
    simple_cmd_print(c);
}
