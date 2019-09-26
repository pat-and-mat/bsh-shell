#ifndef PARSER_H
#define PARSER_H

struct token;
struct vector;

struct parser
{
    struct vector *tokens;
    int i;
};

struct parser *parser_init(struct vector *tokens);
void parser_init_allocated(struct parser *p, struct vector *tokens);
struct token *parser_lookahead(struct parser *p);
void parse_next(struct parser *p);
struct cmd *parser_parse(struct parser *p);

#endif