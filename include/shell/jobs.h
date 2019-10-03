#ifndef JOBS_H
#define JOBS_H

#include <stdbool.h>
#include <sys/types.h>

#define JOB_STATUS_RUNNING 1
#define JOB_STATUS_STOPPED 2
#define JOB_STATUS_DONE 3

struct job
{
    pid_t pid;
    int status;
    char *cmd;
};

void jobs_init();

void jobs_bg_add(pid_t pid, char *name);
struct job *jobs_bg_get(int i);
bool jobs_bg_contains(pid_t pid);
int jobs_bg_count();

void jobs_bg_clean_all();
void jobs_bg_clean_finished();

struct job *jobs_bg_to_fg(pid_t pid);

void jobs_set_fg(pid_t pid, char *name);
struct job jobs_get_fg();

#endif