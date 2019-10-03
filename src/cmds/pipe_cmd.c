#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <wait.h>

#include <cmds/cmd.h>
#include <cmds/pipe_cmd.h>
#include <utils/vector.h>
#include <utils/xmemory.h>
#include <shell/jobs.h>

struct pipe_cmd *pipe_cmd_init()
{
    struct pipe_cmd *pipe_cmd = xmalloc(sizeof(struct pipe_cmd));
    pipe_cmd_init_allocated(pipe_cmd);
    return pipe_cmd;
}

void pipe_cmd_init_allocated(struct pipe_cmd *c)
{
    cmd_init_allocated(&c->base, CMD_T_PIPE_CMD, pipe_cmd_run, pipe_cmd_print);
    c->left = NULL;
    c->right = NULL;
}

struct cmd *pipe_cmd_get_left(struct pipe_cmd *c)
{
    return c->left;
}
void pipe_cmd_set_left(struct pipe_cmd *c, struct cmd *left)
{
    c->left = left;
}

struct cmd *pipe_cmd_get_right(struct pipe_cmd *c)
{
    return c->right;
}

void pipe_cmd_set_right(struct pipe_cmd *c, struct cmd *right)
{
    c->right = right;
}

void pipe_run_pipe_main(struct pipe_cmd *pipe_cmd);
bool pipe_cmd_run(struct cmd *c, bool is_root)
{
    struct pipe_cmd *pipe_cmd = (struct pipe_cmd *)c;

    pid_t pid_right = fork();

    if (pid_right == -1)
        return false;

    if (!pid_right)
    {
        if (setpgid(0, 0) == -1)
            exit(EXIT_FAILURE);
        pipe_run_pipe_main(pipe_cmd);
    }

    int status;
    int flags = 0;
    if (is_root)
    {
        flags = WUNTRACED;
        jobs_set_fg(pid_right, "<cmd name>");
    }
    waitpid(pid_right, &status, flags);

    if (WIFSIGNALED(status) || (WIFEXITED(status) && WEXITSTATUS(status) == EXIT_FAILURE))
        return false;

    return true;
}

void pipe_run_pipe_main(struct pipe_cmd *pipe_cmd)
{
    int pipefd[2];
    pipe(pipefd);

    pid_t pid_left = fork();

    if (pid_left == -1)
    {
        close(pipefd[0]);
        close(pipefd[1]);
        exit(EXIT_FAILURE);
    }

    if (!pid_left)
    {
        close(pipefd[0]);
        if (dup2(pipefd[1], STDOUT_FILENO) == -1 || !cmd_run(pipe_cmd->left, false))
            exit(EXIT_FAILURE);
        exit(EXIT_SUCCESS);
    }

    close(pipefd[1]);
    if (dup2(pipefd[0], STDIN_FILENO) == -1 || !cmd_run(pipe_cmd->right, false))
    {
        waitpid(pid_left, NULL, 0);
        exit(EXIT_FAILURE);
    }

    int status;
    waitpid(pid_left, &status, 0);

    if (WIFSIGNALED(status) || (WIFEXITED(status) && WEXITSTATUS(status) == EXIT_FAILURE))
        exit(EXIT_FAILURE);

    exit(EXIT_SUCCESS);
}

void pipe_cmd_print(struct cmd *c)
{
    struct pipe_cmd *pipe = (struct pipe_cmd *)c;

    if (!pipe->left)
        printf("<error>");
    else
        cmd_print(pipe->left);

    printf(" | ");

    if (!pipe->right)
        printf("<error>");
    else
        cmd_print(pipe->right);
}