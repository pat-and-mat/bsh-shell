#ifndef INFO_H
#define INFO_H

#include <termios.h>
#include <stdbool.h>

int shell_terminal;
struct termios shell_tmodes;
struct termios default_tmodes;

bool shell_info_init();

#endif