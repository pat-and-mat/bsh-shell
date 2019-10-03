#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include <wait.h>

#include <cmds/cmd.h>
#include <cmds/fg_cmd.h>
#include <utils/vector.h>
#include <utils/xmemory.h>
#include <shell/jobs.h>

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

bool fg_cmd_run(struct cmd *c, bool is_root)
{
    struct fg_cmd *fg = (struct fg_cmd *)c;

    int saved_stdout = dup(STDOUT_FILENO);

    if (!simple_cmd_open_redirects(c))
    {
        simple_cmd_close_redirects(c);
        return false;
    }

    if (vector_count(fg->base.args) == 2)
    {
        char *pid_repr = (char *)vector_get(fg->base.args, 1);
        int pid = atoi(pid_repr);
        if (pid == 0 && strcmp(pid_repr, "0") != 0)
        {
            simple_cmd_close_redirects(c);
            return false;
        }

        struct job *job = jobs_bg_to_fg(pid);
        if (!job)
        {
            simple_cmd_close_redirects(c);
            return false;
        }

        simple_cmd_close_redirects(c);

        int status;
        int flags = 0;
        if (is_root)
            flags = WUNTRACED;
        waitpid(job->pid, &status, flags);
        return WIFSTOPPED(status) || (WIFEXITED(status) && WEXITSTATUS(status) == EXIT_SUCCESS);
    }

    simple_cmd_close_redirects(c);
    return false;
}

void fg_cmd_print(struct cmd *c)
{
    simple_cmd_print(c);
}
