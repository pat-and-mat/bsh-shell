#ifndef CMD_H
#define CMD_H

struct cmd
{
    int type;
    int (*run)(struct cmd *c);
};

void cmd_init(struct cmd *c, int type, int (*run)(struct cmd *c));

#endif