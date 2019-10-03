#include <shell/jobs.h>
#include <utils/sighandlers.h>
#include <signal.h>
#include <sys/types.h>
#include <stdlib.h>
#include <wait.h>

void sigstp_handler()
{
    struct job *f = jobs_get_fg();
    kill(f->pid, SIGTSTP);
    waitpid(f->pid, NULL, WUNTRACED);
}

void sigint_handler()
{
    struct job *f = jobs_get_fg();
    kill(f->pid, SIGINT);
}

void sigquit_handler()
{
}