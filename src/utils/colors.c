#include <stdio.h>
#include <string.h>
#include <utils/colors.h>
#include <utils/xmemory.h>

char *build_color(int fg, int bg)
{
    char *color = xmalloc(sizeof(char) * (strlen("\x1B[0;fg;bgm") + 1));
    sprintf(color, "\x1B[0;%d;%dm", 30 + fg, 40 + bg);
    return color;
}

char *build_fg_color(int fg)
{
    char *color = xmalloc(sizeof(char) * (strlen("\x1B[34m") + 1));
    sprintf(color, "\x1B[%dm", 30 + fg);
    return color;
}
