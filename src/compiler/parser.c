#include <string.h>
#include <stdio.h>
#include <stdbool.h>

#include <cmds/cmd.h>
#include <cmds/bg_cmd.h>
#include <cmds/cd_cmd.h>
#include <cmds/left_cmd.h>
#include <cmds/simple_cmd.h>
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
bool parser_parse_bg_cmd(struct parser *p, struct cmd **out, struct cmd *left);
bool parser_parse_sep_cmd(struct parser *p, struct cmd **out, struct cmd *left);
bool parser_parse_cmd_line_2(struct parser *p, struct cmd **out);

bool parser_parse_job(struct parser *p, struct cmd **out);
bool parser_parse_job_1(struct parser *p, struct cmd **out, struct cmd *left);
bool parser_parse_pipe_cmd(struct parser *p, struct cmd **out, struct cmd *left);

bool parser_parse_cmd(struct parser *p, struct cmd **out);
bool parser_parse_simple_cmd(struct parser *p, struct cmd **out, struct vector *redlist);
bool parser_parse_arg_list(struct parser *p, struct cmd **out, struct simple_cmd *left);

bool parser_parse_redirect(struct parser *p, struct cmd **out);
bool parser_parse_redirect_list(struct parser *p, struct vector **out, struct vector *left);

bool parser_parse_left_cmd(struct parser *p, struct cmd **out);
bool parser_parse_right_cmd(struct parser *p, struct cmd **out);
bool parser_parse_right_append_cmd(struct parser *p, struct cmd **out);

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

    int token_t = token_get_type(parser_lookahead(p));
    if (token_t != TOKEN_T_STR && token_t != TOKEN_T_LEFT &&
        token_t != TOKEN_T_RIGHT && token_t != TOKEN_T_RIGHT_APPEND)
        return false;

    struct cmd *job;
    if (!parser_parse_job(p, &job))
        return false;

    return parser_parse_cmd_line_1(p, out, job);
}

bool parser_parse_cmd_line_1(struct parser *p, struct cmd **out, struct cmd *left)
{
    int token_t = token_get_type(parser_lookahead(p));

    if (token_t == TOKEN_T_SEMICOLON)
        return parser_parse_sep_cmd(p, out, left);

    if (token_t == TOKEN_T_BG)
        return parser_parse_bg_cmd(p, out, left);

    if (token_t == TOKEN_T_EOF)
    {
        *out = left;
        return true;
    }

    *out = NULL;
    return false;
}

bool parser_parse_sep_cmd(struct parser *p, struct cmd **out, struct cmd *left)
{
    parser_next(p);

    struct cmd *right;
    if (!parser_parse_cmd_line_2(p, &right))
    {
        *out = NULL;
        return false;
    }

    struct sep_cmd *sep_cmd = sep_cmd_init();
    sep_cmd_set_left(sep_cmd, left);
    sep_cmd_set_right(sep_cmd, right);

    *out = (struct cmd *)sep_cmd;
    return true;
}

bool parser_parse_bg_cmd(struct parser *p, struct cmd **out, struct cmd *left)
{
    parser_next(p);

    struct cmd *right;
    if (!parser_parse_cmd_line_2(p, &right))
    {
        *out = NULL;
        return false;
    }

    struct bg_cmd *bg_cmd = bg_cmd_init();
    bg_cmd_set_left(bg_cmd, left);
    bg_cmd_set_right(bg_cmd, right);

    *out = (struct cmd *)bg_cmd;
    return true;
}

bool parser_parse_cmd_line_2(struct parser *p, struct cmd **out)
{
    int token_t = token_get_type(parser_lookahead(p));

    *out = NULL;

    if (token_t == TOKEN_T_EOF)
        return true;

    if (token_t != TOKEN_T_STR && token_t != TOKEN_T_LEFT &&
        token_t != TOKEN_T_RIGHT && token_t != TOKEN_T_RIGHT_APPEND)
        return false;

    return parser_parse_cmd_line(p, out);
}

bool parser_parse_job(struct parser *p, struct cmd **out)
{
    int token_t = token_get_type(parser_lookahead(p));

    *out = NULL;

    if (token_t != TOKEN_T_STR && token_t != TOKEN_T_LEFT &&
        token_t != TOKEN_T_RIGHT && token_t != TOKEN_T_RIGHT_APPEND)
        return false;

    struct cmd *cmd;
    if (!parser_parse_cmd(p, &cmd))
        return false;

    return parser_parse_job_1(p, out, cmd);
}

bool parser_parse_job_1(struct parser *p, struct cmd **out, struct cmd *left)
{
    int token_t = token_get_type(parser_lookahead(p));

    if (token_t == TOKEN_T_PIPE)
        return parser_parse_pipe_cmd(p, out, left);

    if (token_t == TOKEN_T_SEMICOLON || token_t == TOKEN_T_BG || token_t == TOKEN_T_EOF)
    {
        *out = left;
        return true;
    }

    *out = NULL;
    return false;
}

bool parser_parse_pipe_cmd(struct parser *p, struct cmd **out, struct cmd *left)
{
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

    int token_type = token_get_type(parser_lookahead(p));

    if (token_type != TOKEN_T_STR && token_type != TOKEN_T_LEFT &&
        token_type != TOKEN_T_RIGHT && token_type != TOKEN_T_RIGHT_APPEND)
        return false;

    struct vector *redirects;
    if (!parser_parse_redirect_list(p, &redirects, vector_init()))
        return false;

    token_type = token_get_type(parser_lookahead(p));

    if (token_type != TOKEN_T_STR)
        return false;

    struct cmd *cmd;
    if (!parser_parse_simple_cmd(p, &cmd, redirects))
        return false;

    return parser_parse_arg_list(p, out, (struct simple_cmd *)cmd);
}

bool parser_parse_simple_cmd(struct parser *p, struct cmd **out, struct vector *redirects)
{
    char *token_lex = token_get_lex(parser_lookahead(p));

    struct simple_cmd *simple_cmd;
    if (strcmp(token_lex, "cd") == 0)
        simple_cmd = (struct simple_cmd *)cd_cmd_init();
    else
        simple_cmd = simple_cmd_init(token_lex);

    parser_next(p);

    for (int i = 0; i < vector_count(redirects); i++)
        simple_cmd_add_redirect(simple_cmd, (struct cmd *)vector_get(redirects, i));

    *out = (struct cmd *)simple_cmd;
    return true;
}

bool parser_parse_arg_list(struct parser *p, struct cmd **out, struct simple_cmd *left)
{
    int token_t = token_get_type(parser_lookahead(p));

    if (token_t == TOKEN_T_SEMICOLON || token_t == TOKEN_T_BG ||
        token_t == TOKEN_T_PIPE || token_t == TOKEN_T_EOF)
    {
        *out = (struct cmd *)left;
        return true;
    }

    *out = NULL;

    if (token_t == TOKEN_T_LEFT || token_t == TOKEN_T_RIGHT ||
        token_t == TOKEN_T_RIGHT_APPEND)
    {
        struct cmd *redirect;
        if (!parser_parse_redirect(p, &redirect))
            return false;

        simple_cmd_add_redirect(left, redirect);
        return parser_parse_arg_list(p, out, left);
    }

    if (token_t == TOKEN_T_STR)
    {
        simple_cmd_add_arg(left, token_get_lex(parser_lookahead(p)));
        parser_next(p);
        return parser_parse_arg_list(p, out, left);
    }

    return false;
}

bool parser_parse_redirect_list(struct parser *p, struct vector **out, struct vector *left)
{
    int token_t = token_get_type(parser_lookahead(p));

    if (token_t == TOKEN_T_STR)
    {
        *out = left;
        return true;
    }

    *out = NULL;

    if (token_t == TOKEN_T_LEFT || token_t == TOKEN_T_RIGHT ||
        token_t == TOKEN_T_RIGHT_APPEND)
    {
        struct cmd *redirect;
        if (!parser_parse_redirect(p, &redirect))
            return false;

        vector_add(left, redirect);
        return parser_parse_redirect_list(p, out, left);
    }

    return false;
}

bool parser_parse_redirect(struct parser *p, struct cmd **out)
{
    int token_type = token_get_type(parser_lookahead(p));

    if (token_type == TOKEN_T_LEFT)
        return parser_parse_left_cmd(p, out);

    if (token_type == TOKEN_T_RIGHT)
        return parser_parse_right_cmd(p, out);

    if (token_type == TOKEN_T_RIGHT_APPEND)
        return parser_parse_right_append_cmd(p, out);

    *out = NULL;
    return false;
}

bool parser_parse_left_cmd(struct parser *p, struct cmd **out)
{
    parser_next(p);

    struct token *token = parser_lookahead(p);
    if (token_get_type(token) != TOKEN_T_STR)
    {
        *out = NULL;
        return false;
    }

    *out = (struct cmd *)left_cmd_init(token_get_lex(token));
    return true;
}

bool parser_parse_right_cmd(struct parser *p, struct cmd **out)
{
    parser_next(p);

    struct token *token = parser_lookahead(p);
    if (token_get_type(token) != TOKEN_T_STR)
    {
        *out = NULL;
        return false;
    }

    *out = (struct cmd *)right_cmd_init(token_get_lex(token));
    return true;
}

bool parser_parse_right_append_cmd(struct parser *p, struct cmd **out)
{
    parser_next(p);

    struct token *token = parser_lookahead(p);
    if (token_get_type(token) != TOKEN_T_STR)
    {
        *out = NULL;
        return false;
    }

    *out = (struct cmd *)right_append_cmd_init(token_get_lex(token));
    return true;
}