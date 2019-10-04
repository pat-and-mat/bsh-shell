#include <stdlib.h>
#include <stdbool.h>
#include <signal.h>
#include <wait.h>
#include <shell/jobs.h>
#include <utils/vector.h>
#include <utils/xmemory.h>
#include <shell/info.h>
#include <utils/sigutils.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

struct vector jobs;

void jobs_init()
{
    vector_init_allocated(&jobs);
}

struct job *jobs_job_init(pid_t pid, int status, char *cmd_name)
{
    struct job *job = xmalloc(sizeof(struct job));
    job->pid = pid;
    job->cmd = cmd_name;
    job->status = status;
    tcgetattr(shell_terminal, &job->tmodes);
    return job;
}

bool jobs_run_fg(struct cmd *c)
{
    tcgetattr(shell_terminal, &shell_tmodes);
    tcsetattr(shell_terminal, TCSADRAIN, &default_tmodes);

    pid_t job_pid = fork();
    if (job_pid == -1)
    {
        tcsetattr(shell_terminal, TCSADRAIN, &shell_tmodes);
        return false;
    }

    if (!job_pid)
    {
        signals_default();
        setpgid(0, 0);
        tcsetpgrp(shell_terminal, getpgrp());
        if (!cmd_run_process(c))
            exit(EXIT_FAILURE);
        exit(EXIT_SUCCESS);
    }

    setpgid(job_pid, job_pid);
    tcsetpgrp(shell_terminal, job_pid);

    char *cmd_name = xmalloc(sizeof(char) * 4096);
    cmd_get_str(c, cmd_name);
    struct job *job = jobs_job_init(job_pid, JOB_STATUS_RUNNING, cmd_name);
    bool job_status = wait_for_job(job);

    tcsetpgrp(shell_terminal, getpgrp());
    tcsetattr(shell_terminal, TCSADRAIN, &shell_tmodes);

    return job_status;
}

bool wait_for_job(struct job *job)
{
    int status;
    if (waitpid(job->pid, &status, WUNTRACED) == -1)
        return false;
    if (WIFSTOPPED(status))
    {
        job->status = JOB_STATUS_STOPPED;
        tcgetattr(shell_terminal, &job->tmodes);
        vector_add(&jobs, job);
        return true;
    }
    return WIFEXITED(status) && WEXITSTATUS(status) == EXIT_SUCCESS;
}

bool jobs_run_bg(struct cmd *c)
{
    pid_t job_pid = fork();
    if (job_pid == -1)
        return false;

    if (!job_pid)
    {
        signals_default();
        setpgid(0, 0);
        if (!cmd_run_process(c))
            exit(EXIT_FAILURE);
        exit(EXIT_SUCCESS);
    }

    setpgid(job_pid, job_pid);

    char *cmd_name = xmalloc(sizeof(char) * 4096);
    cmd_get_str(c, cmd_name);
    struct job *job = jobs_job_init(job_pid, JOB_STATUS_RUNNING, cmd_name);
    vector_add(&jobs, job);

    return true;
}

int jobs_count()
{
    return vector_count(&jobs);
}

struct job *jobs_get(int i)
{
    return (struct job *)vector_get(&jobs, i);
}

char *jobs_format_status(int status)
{
    switch (status)
    {
    case JOB_STATUS_DONE:
        return "done";
    case JOB_STATUS_RUNNING:
        return "running";
    case JOB_STATUS_STOPPED:
        return "stopped";
    case JOB_STATUS_FAILED:
        return "failed";
    default:
        return "job mode";
    }
}

bool job_handle_status_update(struct job *job, int status);

void jobs_update()
{
    struct job *job;
    int status;
    for (int i = 0; i < jobs_count(); i++)
    {
        job = jobs_get(i);
        if (waitpid(job->pid, &status, WNOHANG | WUNTRACED) > 0 &&
            job_handle_status_update(job, status))
            vector_delete(&jobs, i--);
    }
}

bool job_handle_status_update(struct job *job, int status)
{
    if (WIFSTOPPED(status))
        job->status = JOB_STATUS_STOPPED;
    else if (WIFEXITED(status))
    {
        if (WEXITSTATUS(status) == EXIT_FAILURE)
            job->status = JOB_STATUS_FAILED;
        else
            job->status = JOB_STATUS_DONE;
    }
    else if (WIFSIGNALED(status))
        job->status = JOB_STATUS_FAILED;

    return job->status = JOB_STATUS_FAILED || job->status == JOB_STATUS_DONE;
}

void jobs_kill()
{
    struct job *job;
    for (int i = 0; i < jobs_count(); i++)
    {
        job = jobs_get(i);
        kill(job->pid, SIGKILL);
    }
    memset(&jobs, 0, sizeof(struct vector));
}

bool jobs_resume_job(struct job *job);

bool jobs_bg_to_fg(pid_t pid)
{
    struct job *job;
    for (int i = 0; i < jobs_count(); i++)
    {
        job = jobs_get(i);
        if (job->pid == pid)
        {
            vector_delete(&jobs, i);
            return jobs_resume_job(job);
        }
    }
    return false;
}

bool jobs_resume_job(struct job *job)
{
    tcgetattr(shell_terminal, &shell_tmodes);
    tcsetattr(shell_terminal, TCSADRAIN, &job->tmodes);

    tcsetpgrp(shell_terminal, job->pid);

    if (kill(job->pid, SIGCONT) == -1)
    {
        tcsetpgrp(shell_terminal, getpgrp());
        tcsetattr(shell_terminal, TCSADRAIN, &shell_tmodes);
        return false;
    }

    tcsetpgrp(shell_terminal, getpgrp());
    tcsetattr(shell_terminal, TCSADRAIN, &shell_tmodes);
    return wait_for_job(job);
}
