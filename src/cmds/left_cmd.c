#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <fcntl.h>

#include <cmds/cmd.h>
#include <cmds/left_cmd.h>
#include <utils/vector.h>
#include <utils/xmemory.h>

struct left_cmd *left_cmd_init(char *filename)
{
    struct left_cmd *left_cmd = xmalloc(sizeof(struct left_cmd));
    left_cmd_init_allocated(left_cmd, filename);
    return left_cmd;
}

void left_cmd_init_allocated(struct left_cmd *c, char *filename)
{
    redirect_cmd_init_allocated(&c->base, filename);
    cmd_init_allocated((struct cmd *)&c->base, CMD_T_LEFT_CMD, left_cmd_run, left_cmd_print);
}

bool left_cmd_run(struct cmd *c)
{
    struct left_cmd *left = (struct left_cmd *)c;

    left->base.fd = open(left->base.filename, O_RDONLY);
    if (left->base.fd == -1)
        return false;

    dup2(left->base.fd, STDIN_FILENO);
    return true;
}

void left_cmd_print(struct cmd *c)
{
    struct left_cmd *left = (struct left_cmd *)c;

    printf("< ");

    if (!left->base.filename)
        printf("<error>");
    else
        printf("%s", left->base.filename);
}
