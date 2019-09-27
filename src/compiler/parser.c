#include <string.h>
#include <stdio.h>
#include <stdbool.h>

#include <cmds/cmd.h>
#include <cmds/bg_cmd.h>
#include <cmds/cd_cmd.h>
#include <cmds/left_cmd.h>
#include <cmds/path_cmd.h>
#include <cmds/pipe_cmd.h>
#include <cmds/right_append_cmd.h>
#include <cmds/right_cmd.h>
#include <cmds/sep_cmd.h>
#include <compiler/parser.h>
#include <compiler/token.h>
#include <utils/vector.h>
#include <utils/xmemory.h>

bool parser_parse_cmd_line(struct parser *p, struct cmd **out);
bool parser_parse_cmd_line_1(struct parser *p, struct cmd **out, struct cmd *left);
bool parser_parse_cmd_line_1_1(struct parser *p, struct cmd **out, struct cmd *left);
bool parser_parse_cmd_line_1_2(struct parser *p, struct cmd **out, struct cmd *left);
bool parser_parse_cmd_line_1_3(struct parser *p, struct cmd **out);

bool parser_parse_job(struct parser *p, struct cmd **out);
bool parser_parse_job_1(struct parser *p, struct cmd **out, struct cmd *left);

bool parser_parse_cmd(struct parser *p, struct cmd **out);
bool parser_parse_cmd_1(struct parser *p, struct cmd **out, struct cmd *left);
bool parser_parse_cmd_1_1(struct parser *p, struct cmd **out, struct cmd *left);
bool parser_parse_cmd_1_2(struct parser *p, struct cmd **out, struct cmd *left);
bool parser_parse_cmd_1_3(struct parser *p, struct cmd **out, struct cmd *left);

bool parser_parse_simple_cmd(struct parser *p, struct cmd **out);
bool parser_parse_cd_cmd(struct parser *p, struct cmd **out);
bool parser_parse_path_cmd(struct parser *p, struct cmd **out);
bool parser_parse_path_cmd_1(struct parser *p, struct cmd **out, struct cmd *left);

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
    p->cmd = NULL;
    p->is_ok = false;
}

struct token *parser_lookahead(struct parser *p)
{
    return vector_get(p->tokens, p->i);
}

void parser_next(struct parser *p)
{
    p->i++;
}

bool parser_get_is_ok(struct parser *p)
{
    return p->is_ok;
}

struct cmd *parser_get_cmd(struct parser *p)
{
    return p->cmd;
}

bool parser_parse(struct parser *p)
{
    p->is_ok = parser_parse_cmd_line(p, &p->cmd);
    if (token_get_type(parser_lookahead(p)) != TOKEN_T_EOF)
    {
        p->is_ok = false;
        p->cmd = NULL;
    }
    return p->is_ok;
}

bool parser_parse_cmd_line(struct parser *p, struct cmd **out)
{
    *out = NULL;

    struct cmd *job;
    if (!parser_parse_job(p, &job))
        return false;
    return parser_parse_cmd_line_1(p, out, job);
}

bool parser_parse_cmd_line_1(struct parser *p, struct cmd **out, struct cmd *left)
{
    struct token *token = parser_lookahead(p);

    if (token_get_type(token) == TOKEN_T_SEMICOLON)
        return parser_parse_cmd_line_1_1(p, out, left);

    if (token_get_type(token) == TOKEN_T_BG)
        return parser_parse_cmd_line_1_2(p, out, left);

    *out = left;
    return true;
}

bool parser_parse_cmd_line_1_1(struct parser *p, struct cmd **out, struct cmd *left)
{
    *out = NULL;

    if (token_get_type(parser_lookahead(p)) != TOKEN_T_SEMICOLON)
        return false;

    parser_next(p);

    struct sep_cmd *sep_cmd = sep_cmd_init();
    sep_cmd_set_left(sep_cmd, left);

    struct cmd *right;
    if (!parser_parse_cmd_line_1_3(p, &right))
        return false;

    sep_cmd_set_right(sep_cmd, right);

    *out = (struct cmd *)sep_cmd;
    return true;
}

bool parser_parse_cmd_line_1_2(struct parser *p, struct cmd **out, struct cmd *left)
{
    *out = NULL;

    if (token_get_type(parser_lookahead(p)) != TOKEN_T_BG)
        return false;

    parser_next(p);

    struct bg_cmd *bg_cmd = bg_cmd_init();
    bg_cmd_set_left(bg_cmd, left);

    struct cmd *right;
    if (!parser_parse_cmd_line_1_3(p, &right))
        return false;

    bg_cmd_set_right(bg_cmd, right);

    *out = (struct cmd *)bg_cmd;
    return true;
}

bool parser_parse_cmd_line_1_3(struct parser *p, struct cmd **out)
{
    parser_parse_cmd_line(p, out);
    return true;
}

bool parser_parse_job(struct parser *p, struct cmd **out)
{
    *out = NULL;

    struct cmd *cmd;
    if (!parser_parse_cmd(p, &cmd))
        return false;
    return parser_parse_job_1(p, out, cmd);
}

bool parser_parse_job_1(struct parser *p, struct cmd **out, struct cmd *left)
{
    *out = left;
    if (token_get_type(parser_lookahead(p)) != TOKEN_T_PIPE)
        return true;

    parser_next(p);

    struct cmd *right;
    if (!parser_parse_cmd(p, &right))
        return false;

    struct pipe_cmd *pipe_cmd = pipe_cmd_init();
    pipe_cmd_set_left(pipe_cmd, left);
    pipe_cmd_set_right(pipe_cmd, right);

    return parser_parse_job_1(p, out, (struct cmd *)pipe_cmd);
}

bool parser_parse_cmd(struct parser *p, struct cmd **out)
{
    *out = NULL;

    struct cmd *simple_cmd;
    if (!parser_parse_simple_cmd(p, &simple_cmd))
        return false;

    return parser_parse_cmd_1(p, out, simple_cmd);
}

bool parser_parse_cmd_1(struct parser *p, struct cmd **out, struct cmd *left)
{
    if (!parser_parse_cmd_1_1(p, out, left) &&
        !parser_parse_cmd_1_2(p, out, left) &&
        !parser_parse_cmd_1_3(p, out, left))
        *out = left;
    return true;
}

bool parser_parse_cmd_1_1(struct parser *p, struct cmd **out, struct cmd *left)
{
    *out = NULL;

    if (token_get_type(parser_lookahead(p)) != TOKEN_T_LEFT)
        return false;

    parser_next(p);

    struct left_cmd *left_cmd = left_cmd_init();
    left_cmd_set_cmd(left_cmd, left);

    struct token *token = parser_lookahead(p);
    if (token_get_type(token) != TOKEN_T_STR)
        return false;

    left_cmd_set_filename(left_cmd, token_get_lex(token));
    parser_next(p);

    *out = (struct cmd *)left_cmd;
    return true;
}

bool parser_parse_cmd_1_2(struct parser *p, struct cmd **out, struct cmd *left)
{
    *out = NULL;

    if (token_get_type(parser_lookahead(p)) != TOKEN_T_RIGHT)
        return false;

    parser_next(p);

    struct right_cmd *right_cmd = right_cmd_init();
    right_cmd_set_cmd(right_cmd, left);

    struct token *token = parser_lookahead(p);
    if (token_get_type(token) != TOKEN_T_STR)
        return false;

    right_cmd_set_filename(right_cmd, token_get_lex(token));
    parser_next(p);

    *out = (struct cmd *)right_cmd;
    return true;
}

bool parser_parse_cmd_1_3(struct parser *p, struct cmd **out, struct cmd *left)
{
    *out = NULL;

    if (token_get_type(parser_lookahead(p)) != TOKEN_T_RIGHT_APPEND)
        return false;

    parser_next(p);

    struct right_append_cmd *right_append_cmd = right_append_cmd_init();
    right_append_cmd_set_cmd(right_append_cmd, left);

    struct token *token = parser_lookahead(p);
    if (token_get_type(token) != TOKEN_T_STR)
        return false;

    right_append_cmd_set_filename(right_append_cmd, token_get_lex(token));
    parser_next(p);

    *out = (struct cmd *)right_append_cmd;
    return true;
}

bool parser_parse_simple_cmd(struct parser *p, struct cmd **out)
{
    return parser_parse_cd_cmd(p, out) ||
           parser_parse_path_cmd(p, out);
}

bool parser_parse_cd_cmd(struct parser *p, struct cmd **out)
{
    *out = NULL;

    struct token *token = parser_lookahead(p);
    if (token_get_type(token) != TOKEN_T_STR ||
        strcmp(token_get_lex(token), "cd") != 0)
        return false;

    parser_next(p);

    struct cd_cmd *cd_cmd = cd_cmd_init();

    token = parser_lookahead(p);
    if (token_get_type(token) == TOKEN_T_STR)
    {
        cd_cmd_set_arg(cd_cmd, token_get_lex(token));
        parser_next(p);
    }

    *out = (struct cmd *)cd_cmd;
    return true;
}

bool parser_parse_path_cmd(struct parser *p, struct cmd **out)
{
    *out = NULL;

    struct token *token = parser_lookahead(p);
    if (token_get_type(token) != TOKEN_T_STR)
        return false;

    struct path_cmd *path_cmd = path_cmd_init();
    path_cmd_add_arg(path_cmd, token_get_lex(token));

    parser_next(p);

    return parser_parse_path_cmd_1(p, out, (struct cmd *)path_cmd);
}

bool parser_parse_path_cmd_1(struct parser *p, struct cmd **out, struct cmd *left)
{
    *out = left;

    struct token *token = parser_lookahead(p);
    if (token_get_type(token) != TOKEN_T_STR)
        return true;

    path_cmd_add_arg((struct path_cmd *)left, token_get_lex(token));
    parser_next(p);

    return parser_parse_path_cmd_1(p, out, left);
}