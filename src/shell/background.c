#include <stdlib.h>
#include <wait.h>
#include <utils/vector.h>
#include <utils/xmemory.h>
#include <shell/background.h>
#include <signal.h>
#include <sys/types.h>

struct vector bg_processes;

void bg_init()
{
    vector_init_allocated(&bg_processes);
}

void bg_clean_all()
{
    struct bg_process *process;
    for (int i = 0; i < vector_count(&bg_processes); i++)
    {
        process = (struct bg_process *)vector_get(&bg_processes, i);
        kill(process->pid, SIGKILL);
        vector_delete(&bg_processes, i);
        i--;
    }
}

void bg_clean_finished()
{
    struct bg_process *process;
    for (int i = 0; i < vector_count(&bg_processes); i++)
    {
        process = (struct bg_process *)vector_get(&bg_processes, i);
        if (waitpid(process->pid, NULL, WNOHANG) > 0)
        {
            vector_delete(&bg_processes, i);
            i--;
        }
    }
}

int bg_count()
{
    return vector_count(&bg_processes);
}

struct bg_process *bg_get(int i)
{
    return (struct bg_process *)vector_get(&bg_processes, i);
}

struct bg_process *bg_process_init(pid_t pid, char *name);
void bg_add(pid_t pid, char *name)
{
    vector_add(&bg_processes, bg_process_init(pid, name));
}

struct bg_process *bg_process_init(pid_t pid, char *name)
{
    struct bg_process *p = xmalloc(sizeof(struct bg_process));
    p->pid = pid;
    p->cmd_name = name;
    return p;
}

struct bg_process *bg_to_fg(pid_t pid)
{
    struct bg_process *process;
    for (int i = 0; i < vector_count(&bg_processes); i++)
    {
        process = (struct bg_process *)vector_get(&bg_processes, i);
        if (process->pid == pid)
        {
            vector_delete(&bg_processes, i);
            return process;
        }
    }
    return NULL;
}

bool bg_contains(pid_t pid)
{
    struct bg_process *process;
    for (int i = 0; i < vector_count(&bg_processes); i++)
    {
        process = (struct bg_process *)vector_get(&bg_processes, i);
        if (process->pid == pid)
            return true;
    }
    return false;
}