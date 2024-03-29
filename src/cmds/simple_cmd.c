#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/types.h>
#include <libgen.h>
#include <wait.h>

#include <cmds/cmd.h>
#include <cmds/simple_cmd.h>
#include <cmds/redirect_cmd.h>
#include <utils/vector.h>
#include <utils/xmemory.h>
#include <shell/jobs.h>

struct simple_cmd *simple_cmd_init(char *cmd)
{
    struct simple_cmd *simple_cmd = xmalloc(sizeof(struct simple_cmd));
    simple_cmd_init_allocated(simple_cmd, cmd);
    return simple_cmd;
}

bool simple_cmd_run_process(struct cmd *c);
void simple_cmd_init_allocated(struct simple_cmd *c, char *cmd)
{
    cmd_init_allocated(&c->base, CMD_T_SIMPLE_CMD,
                       jobs_run_fg,
                       simple_cmd_run_process,
                       simple_cmd_print,
                       simple_cmd_get_str);
    c->args = vector_init();
    c->redirects = vector_init();
    c->saved_stdin = -1;
    c->saved_stdout = -1;
    simple_cmd_add_arg(c, cmd);
}

void simple_cmd_add_arg(struct simple_cmd *c, char *arg)
{
    vector_add(c->args, arg);
}

void simple_cmd_add_redirect(struct simple_cmd *c, struct cmd *redirect)
{
    vector_add(c->redirects, redirect);
}

bool simple_cmd_run_process(struct cmd *c)
{
    struct simple_cmd *simple = (struct simple_cmd *)c;

    if (!simple_cmd_open_redirects(c))
    {
        simple_cmd_close_redirects(c);
        return false;
    }

    pid_t pid = fork();
    if (pid == -1)
    {
        simple_cmd_close_redirects(c);
        return false;
    }

    if (!pid)
    {
        char *args[vector_count(simple->args) + 1];
        args[0] = basename((char *)vector_get(simple->args, 0));
        for (int i = 1; i < vector_count(simple->args); i++)
            args[i] = (char *)vector_get(simple->args, i);
        args[vector_count(simple->args)] = NULL;

        if (execvp((char *)vector_get(simple->args, 0), args) == -1)
            exit(EXIT_FAILURE);
    }

    int status;
    waitpid(pid, &status, 0);
    simple_cmd_close_redirects(c);

    return WIFEXITED(status) && WEXITSTATUS(status) == EXIT_SUCCESS;
}

bool simple_cmd_open_redirects(struct cmd *c)
{
    struct simple_cmd *simple = (struct simple_cmd *)c;

    simple->saved_stdin = dup(STDIN_FILENO);
    simple->saved_stdout = dup(STDOUT_FILENO);

    for (int i = 0; i < vector_count(simple->redirects); i++)
        if (!cmd_run_process((struct cmd *)vector_get(simple->redirects, i)))
            return false;
    return true;
}

void simple_cmd_close_redirects(struct cmd *c)
{
    struct simple_cmd *simple = (struct simple_cmd *)c;
    for (int i = 0; i < vector_count(simple->redirects); i++)
        redirect_cmd_close((struct redirect_cmd *)vector_get(simple->redirects, i));

    if (simple->saved_stdin != -1)
    {
        dup2(simple->saved_stdin, STDIN_FILENO);
        close(simple->saved_stdin);
    }
    if (simple->saved_stdout != -1)
    {
        dup2(simple->saved_stdout, STDOUT_FILENO);
        close(simple->saved_stdout);
    }
}

void simple_cmd_print(struct cmd *c)
{
    struct simple_cmd *path = (struct simple_cmd *)c;

    if (vector_count(path->args) == 0)
        printf("<error>");
    else
        printf("%s", (char *)vector_get(path->args, 0));

    for (int i = 1; i < vector_count(path->args); i++)
        printf(" %s", (char *)vector_get(path->args, i));

    struct cmd *redirect;
    for (int i = 0; i < vector_count(path->redirects); i++)
    {
        printf(" ");
        redirect = vector_get(path->redirects, i);
        cmd_print(redirect);
    }
}

void simple_cmd_get_str(struct cmd *c, char *str)
{
    struct simple_cmd *path = (struct simple_cmd *)c;

    if (vector_count(path->args) == 0)
        sprintf(str + strlen(str), "<error>");
    else
        sprintf(str + strlen(str), "%s", (char *)vector_get(path->args, 0));

    for (int i = 1; i < vector_count(path->args); i++)
        sprintf(str + strlen(str), " %s", (char *)vector_get(path->args, i));

    struct cmd *redirect;
    for (int i = 0; i < vector_count(path->redirects); i++)
    {
        sprintf(str + strlen(str), " ");
        redirect = vector_get(path->redirects, i);
        cmd_print(redirect);
    }
}