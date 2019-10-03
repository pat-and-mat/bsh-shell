#include <cmds/redirect_cmd.h>
#include <unistd.h>

void redirect_cmd_init_allocated(struct redirect_cmd *c, char *filename)
{
    c->fd = -1;
    c->filename = filename;
}

void redirect_cmd_close(struct redirect_cmd *c, bool is_root)
{
    if (c->fd != -1)
        close(c->fd);
    c->fd = -1;
}