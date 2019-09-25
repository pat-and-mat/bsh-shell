#include <stdlib.h>

#include <compiler/parser.h>
#include <cmds/path_cmd.h>
#include <utils/vector.h>
#include <compiler/token.h>

struct path_cmd *parser_parse_path_cmd(struct parser *p);

void parser_init(struct parser *p, struct vector *tokens)
{
    p->i = 0;
    p->tokens = vector_copy(tokens);
}

void parser_free(struct parser *p)
{
    vector_free(p->tokens);
    free(p->tokens);
}

struct parser *parser_copy(struct parser *p)
{
    struct parser *cpy = malloc(sizeof(struct parser));
    cpy->i = 0;
    cpy->tokens = vector_copy(p->tokens);
}

struct token *parser_lookahead(struct parser *p)
{
    return vector_get(p->tokens, p->i);
}

void parse_next(struct parser *p)
{
    p->i++;
}

struct cmd *parser_parse(struct parser *p)
{
    return (struct cmd *)parser_parse_path_cmd(p);
}

struct path_cmd *parser_parse_path_cmd(struct parser *p)
{
    struct path_cmd *path_cmd = malloc(sizeof(struct path_cmd));
    path_cmd_init(path_cmd);

    struct token *t = parser_lookahead(p);
    while (token_get_type(t) == TOKEN_T_STR)
        path_cmd_add_arg(path_cmd, token_get_lex(t));

    return path_cmd;
}
