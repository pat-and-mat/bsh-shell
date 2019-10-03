#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <fcntl.h>

#include <cmds/cmd.h>
#include <cmds/right_append_cmd.h>
#include <utils/vector.h>
#include <utils/xmemory.h>

struct right_append_cmd *right_append_cmd_init(char *filename)
{
    struct right_append_cmd *right_append_cmd = xmalloc(sizeof(struct right_append_cmd));
    right_append_cmd_init_allocated(right_append_cmd, filename);
    return right_append_cmd;
}

void right_append_cmd_init_allocated(struct right_append_cmd *c, char *filename)
{
    redirect_cmd_init_allocated(&c->base, filename);
    cmd_init_allocated((struct cmd *)&c->base, CMD_T_LEFT_CMD, right_append_cmd_run, right_append_cmd_print);
}

bool right_append_cmd_run(struct cmd *c)
{
    struct right_append_cmd *right_append = (struct right_append_cmd *)c;

    right_append->base.fd = open(right_append->base.filename, O_RDWR | O_CREAT | O_APPEND, 0777);
    if (right_append->base.fd == -1)
        return false;

    if (dup2(right_append->base.fd, STDOUT_FILENO) == -1)
        return false;

    return true;
}

void right_append_cmd_print(struct cmd *c)
{
    struct right_append_cmd *right_append = (struct right_append_cmd *)c;

    printf(">> ");

    if (!right_append->base.filename)
        printf("<error>");
    else
        printf("%s", right_append->base.filename);
}
