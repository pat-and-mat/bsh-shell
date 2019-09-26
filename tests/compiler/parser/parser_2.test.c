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

    struct token t1;
    struct token t2;
    struct parser p;
    struct vector v;
    struct cmd *c;

    char *string1 = "rodrigo";
    token_init(&t1, TOKEN_T_STR, string1);

    char *string2 = "$";
    token_init(&t2, TOKEN_T_EOF, string2);

    vector_init(&v);

    vector_add(&v, &t1);
    vector_add(&v, &t2);

    parser_init(&p, &v);

    c = parser_parse(&p);

    struct path_cmd *pc = (struct path_cmd *)c;

    char *tok = vector_get(pc->args, 0);

    if (!strcmp(tok, "rodrigo"))
    {
        xmem_free();
        return 0;
    }

    xmem_free();
    return -1;
}