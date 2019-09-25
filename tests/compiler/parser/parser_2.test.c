#include <stdlib.h>
#include <string.h>

#include <compiler/parser.h>
#include <cmds/path_cmd.h>
#include <utils/vector.h>
#include <compiler/token.h>

int main()
{
    struct parser p;
    struct vector v;
    struct cmd *c;

    vector_init(&v);
    char *token1 = "rodrigo";
    vector_add(&v, token1, strlen(token1));

    parser_init(&p, &v);
    c = parser_parse(&p);

    struct path_cmd *pc = (struct path_cmd *)c;

    char *vec = vector_get(pc->args, 0);
    return 0;
    int a = strcmp(vec, token1);

    if (a)
    {
        return 0;
    }

    return -1;
}