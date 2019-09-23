#ifndef PARSER_H
#define PARSER_H

struct token;
struct vector;

struct parser
{
    struct vector *tokens;
    int i;
};

void parser_init(struct parser *p, struct vector *tokens);
void parser_free(struct parser *p);

struct token *parser_lookahead(struct parser *p);
void parse_next(struct parser *p);

struct cmd *parser_parse(struct parser *p);

#endif