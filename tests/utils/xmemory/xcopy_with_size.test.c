#include <string.h>

#include <utils/xmemory.h>

int main()
{
    char *s = xcopy_with_size("Hola", 5);
    if (strcmp(s, "Hola") != 0)
        return -1;
    xfree(s);
    return 0;
}