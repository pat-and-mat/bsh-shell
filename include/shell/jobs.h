#ifndef JOBS_H
#define JOBS_H

#include <stdbool.h>
#include <sys/types.h>

#define STATUS_RUNNING
#define STATUS_STOPPED
#define STATUS_DONE

struct job
{
    pid_t pid;
    int status;
    char *cmd_name;
};

void jobs_init();
int jobs_bg_count();
struct job *jobs_bg_get(int i);
void jobs_bg_clean_all();
void jobs_bg_clean_finished();
void jobs_bg_add(pid_t pid, char *name);
struct job *jobs_bg_to_fg(pid_t pid);
bool jobs_bg_contains(pid_t pid);

void jobs_set_fg(pid_t gpid, char *name);
struct job jobs_get_fg();

#endif