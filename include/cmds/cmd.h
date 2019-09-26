#ifndef CMD_H
#define CMD_H

#define CMD_T_PATH_CMD 1

struct cmd
{
    int type;
    int (*run)(struct cmd *c);
};

void cmd_init_allocated(struct cmd *c, int type, int (*run)(struct cmd *c));
int cmd_get_type(struct cmd *c);
int cmd_run(struct cmd *c);

#endif