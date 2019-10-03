#include <stdlib.h>
#include <wait.h>
#include <utils/vector.h>
#include <utils/xmemory.h>
#include <shell/jobs.h>
#include <signal.h>
#include <sys/types.h>

struct vector bg_processes;
struct job *foreground;

void jobs_init()
{
    vector_init_allocated(&bg_processes);
    foreground = NULL;
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

int jobs_bg_count()
{
    return vector_count(&bg_processes);
}

struct job *jobs_bg_get(int i)
{
    return (struct job *)vector_get(&bg_processes, i);
}

struct job *jobs_bg_process_init(pid_t pid, char *name);
void bg_add(pid_t pid, char *name)
{
    vector_add(&bg_processes, bg_process_init(pid, name));
}

struct job *jobs_bg_process_init(pid_t pid, char *name)
{
    struct job *p = xmalloc(sizeof(struct job));
    p->pid = pid;
    p->cmd_name = name;
    return p;
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
            return job;
        }
    }
    return NULL;
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