#ifndef REDIRECT_H
#define REDIRECT_H

#include <cmds/cmd.h>

struct redirect_cmd
{
    struct cmd base;
    int fd;
    char *filename;
};

void redirect_cmd_init_allocated(struct redirect_cmd *c, char *filename);
void redirect_cmd_close(struct redirect_cmd *c);

#endif