#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <compiler/token.h>

int main()
{
    struct token t;
    char *str = "ls";

    token_init(&t, TOKEN_T_STR, str);

    if (token_get_type(&t) != 1)
    {
        return -1;
    }

    return 0;
}