#ifndef CMD_H
#define CMD_H

#include <stdbool.h>

#define CMD_T_SEP_CMD 1
#define CMD_T_BG_CMD 2
#define CMD_T_PIPE_CMD 3
#define CMD_T_LEFT_CMD 4
#define CMD_T_RIGHT_CMD 5
#define CMD_T_RIGHT_APPEND_CMD 6
#define CMD_T_SIMPLE_CMD 7
#define CMD_T_CD 8

struct cmd
{
    int type;
    bool (*run)(struct cmd *c);
    void (*print)(struct cmd *c);
};

void cmd_init_allocated(struct cmd *c, int type, bool (*run)(struct cmd *c, bool is_root), void (*print)(struct cmd *c));
int cmd_get_type(struct cmd *c);
bool cmd_run(struct cmd *c, bool is_root);
void cmd_print(struct cmd *c);

#endif