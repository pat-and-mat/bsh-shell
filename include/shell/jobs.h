#ifndef JOBS_H
#define JOBS_H

#include <stdbool.h>
#include <sys/types.h>
#include <termios.h>
#include <cmds/cmd.h>

#define JOB_STATUS_RUNNING 1
#define JOB_STATUS_STOPPED 2
#define JOB_STATUS_DONE 3
#define JOB_STATUS_FAILED 4

struct job
{
    pid_t pid;
    int status;
    bool notified;
    char *cmd;
    struct termios tmodes;
};

void jobs_init();
struct job *jobs_job_init(pid_t pid, int status, char *cmd_name);

bool jobs_run_fg(struct cmd *c);
bool jobs_run_bg(struct cmd *c);

bool wait_for_job(struct job *job);

bool jobs_bg_to_fg(pid_t pid);

int jobs_count();
struct job *jobs_get(int i);
char *jobs_format_status(int status);

void jobs_update(bool all);
void jobs_kill();

#endif