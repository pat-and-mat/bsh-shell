#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include <compiler/parser.h>
#include <cmds/path_cmd.h>
#include <utils/vector.h>
#include <utils/xmemory.h>
#include <compiler/token.h>

bool parser_parse_cmd_line(struct parser *p, struct cmd **out);
bool parser_parse_cmd_line_1(struct parser *p, struct cmd **out, struct cmd *left);
bool parser_parse_cmd_line_2(struct parser *p, struct cmd **out, struct cmd *left);

bool parser_parse_job(struct parser *p, struct cmd **out);
bool parser_parse_job1(struct parser *p, struct cmd **out, struct cmd *left);

bool parser_parse_cmd(struct parser *p, struct cmd **out);
bool parser_parse_cmd_1(struct parser *p, struct cmd **out, struct cmd *left);

bool parser_parse_simple_cmd(struct parser *p, struct cmd **out);
bool parser_parse_token_list(struct parser *p, struct cmd **out);

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
    struct cmd *cmd;
    if (parser_parse_cmd_line(p, &cmd))
        return cmd;
    return NULL;
}

bool parser_parse_cmd_line(struct parser *p, struct cmd **out)
{
    struct cmd *job, *result;
    if (!parser_parse_job(p, &job))
        return false;
    return parser_parse_cmd_line_1(p, &result, job) || parser_parse_cmd_line_2(p, &result, job);
}

bool parser_parse_cmd_line_1(struct parser *p, struct cmd **out, struct cmd *left)
{
}

bool parser_parse_cmd_line_2(struct parser *p, struct cmd **out, struct cmd *left);

bool parser_parse_job(struct parser *p, struct cmd **out);
bool parser_parse_job1(struct parser *p, struct cmd **out, struct cmd *left);

bool parser_parse_cmd(struct parser *p, struct cmd **out);
bool parser_parse_cmd_1(struct parser *p, struct cmd **out, struct cmd *left);

bool parser_parse_simple_cmd(struct parser *p, struct cmd **out);
bool parser_parse_token_list(struct parser *p, struct cmd **out);