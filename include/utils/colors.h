#ifndef COLORS_H
#define COLORS_H

#define COLOR_BLACK 0
#define COLOR_RED 1
#define COLOR_GREEN 2
#define COLOR_YELLOW 3
#define COLOR_BLUE 4
#define COLOR_MAGENTA 5
#define COLOR_CYAN 6
#define COLOR_WHITE 7

#define COLOR_RESET "\x1B[0m"

char *build_color(int fg, int bg);
char *build_fg_color(int fg);

#endif