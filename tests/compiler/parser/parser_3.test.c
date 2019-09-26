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
    struct token t3;
    struct token t4;
    struct parser p;
    struct vector v;
    struct cmd *c;

    char *string1 = "rodrigo";
    token_init(&t1, TOKEN_T_STR, string1);

    char *string2 = "George";
    token_init(&t2, TOKEN_T_STR, string2);

    char *string3 = "Garcia";
    token_init(&t3, TOKEN_T_STR, string3);

    char *string4 = "$";
    token_init(&t4, TOKEN_T_EOF, string4);

    vector_init(&v);

    vector_add(&v, &t1);
    vector_add(&v, &t2);
    vector_add(&v, &t3);
    vector_add(&v, &t4);

    parser_init(&p, &v);

    c = parser_parse(&p);

    struct path_cmd *pc = (struct path_cmd *)c;

    char *tok1 = vector_get(pc->args, 0);
    char *tok2 = vector_get(pc->args, 1);
    char *tok3 = vector_get(pc->args, 2);

    if (!strcmp(tok1, "rodrigo") && !strcmp(tok2, "George") && !strcmp(tok3, "Garcia"))
    {
        xmem_free();
        return 0;
    }

    xmem_free();
    return -1;
}