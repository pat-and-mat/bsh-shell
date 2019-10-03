#include <cmds/cmd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <shell/info.h>
#include <shell/jobs.h>

void cmd_init_allocated(struct cmd *c, int type,
                        bool (*run_job)(struct cmd *c),
                        bool (*run_process)(struct cmd *c),
                        void (*print)(struct cmd *c))
{
    c->type = type;
    c->run_job = run_job;
    c->run_process = run_process;
    c->print = print;
}

int cmd_get_type(struct cmd *c)
{
    return c->type;
}

bool cmd_run_job(struct cmd *c)
{
    return (*c->run_job)(c);
}

bool cmd_run_process(struct cmd *c)
{
    return (*c->run_process)(c);
}

void cmd_print(struct cmd *c)
{
    (*c->print)(c);
}

void cmd_get_str(struct cmd *c, char *str)
{
    sprintf(str, "<cmd name>");
}