#include <stdlib.h>
#include <string.h>

#include <compiler/parser.h>
#include <cmds/path_cmd.h>
#include <utils/vector.h>
#include <compiler/token.h>
#include <utils/xmemory.h>

int main()
{
    xmem_init();

    struct vector *v = vector_init();

    vector_add(v, token_init(TOKEN_T_STR, "rodrigo"));
    vector_add(v, token_init(TOKEN_T_EOF, "$"));

    struct parser *p = parser_init(v);
    struct cmd *c = parser_parse(p);

    if (c->type != CMD_T_PATH_CMD)
    {
        xmem_free();
        return -1;
    }

    xmem_free();
    return 0;
}