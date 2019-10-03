#include <stdlib.h>
#include <signal.h>
#include <wait.h>
#include <shell/jobs.h>

struct vector bg_processes;
struct job fg_process;

void jobs_init()
{
    vector_init_allocated(&bg_processes);
    fg_process.pid = -1;
    fg_process.cmd = NULL;
    fg_process.status = JOB_STATUS_DONE;
}

struct job *jobs_job_init(pid_t pid, char *name);
void jobs_bg_add(pid_t pid, char *name)
{
    vector_add(&bg_processes, jobs_job_init(pid, name));
}

struct job *jobs_job_init(pid_t pid, char *name)
{
    struct job *p = xmalloc(sizeof(struct job));
    p->pid = pid;
    p->cmd = name;
    return p;
}

struct job *jobs_bg_get(int i)
{
    return (struct job *)vector_get(&bg_processes, i);
}

bool jobs_bg_contains(pid_t pid)
{
    struct job *job;
    for (int i = 0; i < vector_count(&bg_processes); i++)
    {
        job = (struct job *)vector_get(&bg_processes, i);
        if (job->pid == pid)
            return true;
    }
    return false;
}

int jobs_bg_count()
{
    return vector_count(&bg_processes);
}

void jobs_bg_clean_all()
{
    struct job *job;
    for (int i = 0; i < vector_count(&bg_processes); i++)
    {
        job = (struct job *)vector_get(&bg_processes, i);
        kill(job->pid, SIGKILL);
        vector_delete(&bg_processes, i);
        i--;
    }
}

void jobs_bg_clean_finished()
{
    struct job *job;
    for (int i = 0; i < vector_count(&bg_processes); i++)
    {
        job = (struct job *)vector_get(&bg_processes, i);
        if (waitpid(job->pid, NULL, WNOHANG) > 0)
        {
            vector_delete(&bg_processes, i);
            i--;
        }
    }
}

struct job *jobs_bg_to_fg(pid_t pid)
{
    struct job *job;
    for (int i = 0; i < vector_count(&bg_processes); i++)
    {
        job = (struct job *)vector_get(&bg_processes, i);
        if (job->pid == pid)
        {
            vector_delete(&bg_processes, i);
            jobs_set_fg(job->pid, job->cmd);
            return job;
        }
    }
    return NULL;
}

void jobs_set_fg(pid_t pid, char *name)
{
    fg_process.pid = pid;
    fg_process.cmd = name;
}

struct job jobs_get_fg()
{
    return fg_process;
}