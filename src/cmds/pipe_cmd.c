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

bool pipe_cmd_run(struct cmd *c, bool is_root)
{
    struct pipe_cmd *pipe_cmd = (struct pipe_cmd *)c;

    int pipefd[2];
    pipe(pipefd);

    pid_t pid_left = fork();

    if (pid_left == -1)
    {
        close(pipefd[0]);
        close(pipefd[1]);
        return false;
    }

    if (!pid_left)
    {
        close(pipefd[0]);
        if (dup2(pipefd[1], STDOUT_FILENO) == -1 || !cmd_run(pipe_cmd->left, false))
            exit(EXIT_FAILURE);
        exit(EXIT_SUCCESS);
    }

    pid_t pid_right = fork();

    if (pid_right == -1)
    {
        close(pipefd[0]);
        close(pipefd[1]);
        return false;
    }

    if (!pid_right)
    {
        close(pipefd[1]);
        if (dup2(pipefd[0], STDIN_FILENO) == -1 || !cmd_run(pipe_cmd->right, false))
            exit(EXIT_FAILURE);
        exit(EXIT_SUCCESS);
    }

    close(pipefd[0]);
    close(pipefd[1]);

    int right_status;
    int left_status;

    waitpid(pid_left, &left_status, 0);
    waitpid(pid_right, &right_status, 0);
    return WIFEXITED(left_status) && WEXITSTATUS(left_status) == EXIT_SUCCESS &&
           WIFEXITED(right_status) && WEXITSTATUS(right_status) == EXIT_SUCCESS;
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