#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <pwd.h>
#include <sys/types.h>

#include <shell/prompt.h>
#include <utils/xmemory.h>
#include <utils/colors.h>

#define PROMPT_SEP "\ue0b0"

void print_cwd();

int fg_color;
int bg_color;

void print_prompt()
{
    print_cwd();

    printf("%s%s ", build_fg_color(bg_color), PROMPT_SEP);
    printf(COLOR_RESET);
}

char *fix_home_prefix(char *cwd, char *homedir);
void print_cwd()
{
    fg_color = COLOR_BLACK;
    bg_color = COLOR_BLUE;

    char *cwd = getcwd(NULL, 0);
    xmem_add_manually_allocated(cwd);
    cwd = fix_home_prefix(cwd, getpwuid(getuid())->pw_dir);

    printf("%s%s", build_color(fg_color, bg_color), cwd);
    printf(COLOR_RESET);
}

char *fix_home_prefix(char *cwd, char *homedir)
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
