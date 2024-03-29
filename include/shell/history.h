#ifndef HISTORY_H
#define HISTORY_H

void history_init(char *filename);
void history_set_histn(int histn);
void history_load();
void history_save();
void history_add(char *cmd_line);
int history_count();
char *history_get(int i);
char *history_last();
char *history_last_starting(char *preffix);

#endif