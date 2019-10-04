#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>

#include <cmds/cmd.h>
#include <cmds/history_cmd.h>
#include <utils/vector.h>
#include <utils/xmemory.h>
#include <shell/history.h>

struct history_cmd *history_cmd_init()
{
    struct history_cmd *history_cmd = xmalloc(sizeof(struct history_cmd));
    history_cmd_init_allocated(history_cmd);
    return history_cmd;
}

void history_cmd_init_allocated(struct history_cmd *c)
{
    simple_cmd_init_allocated(&c->base, "history");
    cmd_init_allocated((struct cmd *)(&c->base), CMD_T_CD,
                       history_cmd_run,
                       history_cmd_run,
                       simple_cmd_print,
                       simple_cmd_get_str);
}

bool history_cmd_run(struct cmd *c)
{
    struct history_cmd *history = (struct history_cmd *)c;

    if (!simple_cmd_open_redirects(c))
    {
        simple_cmd_close_redirects(c);
        return false;
    }

    if (vector_count(history->base.args) == 1)
    {
        for (int i = 0; i < history_count(); i++)
            printf("%d - %s\n", i, history_get(i));

        simple_cmd_close_redirects(c);
        return true;
    }

    simple_cmd_close_redirects(c);
    return false;
}