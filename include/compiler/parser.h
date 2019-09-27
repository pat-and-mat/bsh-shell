#ifndef PARSER_H
#define PARSER_H

#include <stdbool.h>

struct token;
struct vector;

struct parser
{
    bool is_ok;
    struct cmd *cmd;
    struct vector *tokens;
    int i;
};

struct parser *parser_init(struct vector *tokens);
void parser_init_allocated(struct parser *p, struct vector *tokens);
struct token *parser_lookahead(struct parser *p);
void parser_next(struct parser *p);
bool parser_parse(struct parser *p);

#endif