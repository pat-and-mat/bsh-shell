#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <stdbool.h>
#include <sys/types.h>

struct bg_process
{
    pid_t pid;
    char *cmd_name;
};

void bg_init();
int bg_count();
struct bg_process *bg_get(int i);
void bg_clean_all();
void bg_clean_finished();
void bg_add(pid_t pid, char *name);
struct bg_process *bg_to_fg(pid_t pid);
bool bg_contains(pid_t pid);

#endif