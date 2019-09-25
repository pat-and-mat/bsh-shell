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

    // if (c->type != CMD_T_PATH_CMD)
    // {
    //     return -1;
    // }

    return 0;
}