#include <stdlib.h>
#include <stdio.h>

#include <compiler/parser.h>
#include <cmds/path_cmd.h>
#include <utils/vector.h>
#include <utils/xmemory.h>
#include <compiler/token.h>

struct cmd *parser_parse_path_cmd(struct parser *p);

struct parser *parser_init(struct vector *tokens)
{
    struct parser *parser = xmalloc(sizeof(struct parser));
    parser_init_allocated(parser, tokens);
    return parser;
}

void parser_init_allocated(struct parser *p, struct vector *tokens)
{
    p->i = 0;
    p->tokens = tokens;
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
    return parser_parse_path_cmd(p);
}

struct cmd *parser_parse_path_cmd(struct parser *p)
{
}
