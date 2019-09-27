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

bool parser_get_is_ok(struct parser *p);
struct cmd *parser_get_cmd(struct parser *p);

bool parser_parse(struct parser *p);

#endif