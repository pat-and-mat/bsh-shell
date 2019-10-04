#ifndef SIMPLE_CMD_H
#define SIMPLE_CMD_H

#include <cmds/cmd.h>

struct vector;

struct simple_cmd
{
    struct cmd base;
    struct vector *args;
    struct vector *redirects;
    int saved_stdin;
    int saved_stdout;
};

struct simple_cmd *simple_cmd_init(char *cmd);
void simple_cmd_init_allocated(struct simple_cmd *c, char *cmd);
void simple_cmd_add_arg(struct simple_cmd *c, char *arg);
void simple_cmd_add_redirect(struct simple_cmd *c, struct cmd *redirect);
bool simple_cmd_open_redirects(struct cmd *c);
void simple_cmd_close_redirects(struct cmd *c);
void simple_cmd_print(struct cmd *c);

#endif