#ifndef CMD_H
#define CMD_H

struct cmd
{
    int type;
    int (*run)(struct cmd *c);
};

void init_cmd(struct cmd *c, int type, int (*run)(struct cmd *c));

#endif