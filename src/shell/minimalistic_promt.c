#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <pwd.h>
#include <sys/types.h>

#include <shell/minimalistic_prompt.h>
#include <utils/xmemory.h>
#include <utils/colors.h>

void print_minimalistic_cwd();
void print_minimalistic_end(bool last_cmd_status);

void print_minimalistic_prompt(bool last_cmd_status)
{
    print_minimalistic_cwd();
    print_minimalistic_end(last_cmd_status);

    printf(COLOR_RESET);
}

char *fix_home_prefix_minimalistic(char *cwd, char *homedir);
void print_minimalistic_cwd()
{
    char *cwd = getcwd(NULL, 0);
    xmem_add_manually_allocated(cwd);
    cwd = fix_home_prefix_minimalistic(cwd, getpwuid(getuid())->pw_dir);

    printf("%s%s> ", build_fg_color(COLOR_BLUE), cwd);
    printf(COLOR_RESET);
}

char *fix_home_prefix_minimalistic(char *cwd, char *homedir)
{
    if (strlen(cwd) < strlen(homedir))
        return cwd;

    int i;
    for (i = 0; i < strlen(homedir); i++)
        if (homedir[i] != cwd[i])
            return cwd;

    cwd[--i] = '~';
    return cwd + i;
}

void print_minimalistic_end(bool last_cmd_status)
{
    int color = COLOR_GREEN;
    if (!last_cmd_status)
        color = COLOR_RED;
    printf("%sbsh> ", build_fg_color(color));

    printf(COLOR_RESET);
}
