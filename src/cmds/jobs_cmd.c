#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>

#include <shell/jobs.h>
#include <cmds/cmd.h>
#include <cmds/jobs_cmd.h>
#include <utils/vector.h>
#include <utils/xmemory.h>

struct jobs_cmd *jobs_cmd_init()
{
    struct jobs_cmd *jobs_cmd = xmalloc(sizeof(struct jobs_cmd));
    jobs_cmd_init_allocated(jobs_cmd);
    return jobs_cmd;
}

void jobs_cmd_init_allocated(struct jobs_cmd *c)
{
    simple_cmd_init_allocated(&c->base, "jobs");
    cmd_init_allocated((struct cmd *)(&c->base), CMD_T_CD,
                       jobs_cmd_run,
                       jobs_cmd_run,
                       simple_cmd_print,
                       simple_cmd_get_str);
}

bool jobs_cmd_run(struct cmd *c)
{
    struct jobs_cmd *jobs = (struct jobs_cmd *)c;

    if (!simple_cmd_open_redirects(c))
    {
        simple_cmd_close_redirects(c);
        return false;
    }

    if (vector_count(jobs->base.args) == 1)
    {
        struct job *job;
        for (int i = 0; i < jobs_count(); i++)
        {
            job = jobs_get(i);
            jobs_update(true);
        }
        simple_cmd_close_redirects(c);
        return true;
    }

    simple_cmd_close_redirects(c);
    return false;
}