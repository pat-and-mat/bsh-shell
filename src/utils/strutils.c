#include <utils/strutils.h>
#include <string.h>
#include <stdlib.h>

char *str_copy(char *str)
{
    char *cpy = malloc(sizeof(char) * (strlen(str) + 1));
    strcpy(cpy, str);
    return cpy;
}
