#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <compiler/token.h>
#include <utils/xmemory.h>

int main()
{
    xmem_init();
    struct token t;
    char *str = "ls";

    token_init(&t, TOKEN_T_STR, str);

    if (token_get_type(&t) != 1)
    {
        return -1;
    }

    char *str2 = "ls";

    if (strcmp(token_get_lex(&t), str2))
    {
        xmem_free();
        return -1;
    }

    xmem_free();
    return 0;
}