#include <stdio.h>
#include <string.h>
#include <shell/info.h>
#include <fcntl.h>

bool shell_info_init()
{
    char *term = ctermid(NULL);
    if (strlen(term) == 0)
        return false;

    shell_terminal = open(term, O_RDWR);
    if (shell_terminal == -1)
        return false;

    tcgetattr(shell_terminal, &default_tmodes);
}