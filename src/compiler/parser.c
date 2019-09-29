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
#include <compiler/token_stream.h>
#include <compiler/token.h>
#include <utils/vector.h>
#include <utils/xmemory.h>

bool parser_parse_cmd_line(struct token_stream *stream, struct cmd **out);
bool parser_parse_cmd_line_1(struct token_stream *stream, struct cmd **out, struct cmd *left);
bool parser_parse_bg_cmd(struct token_stream *stream, struct cmd **out, struct cmd *left);
bool parser_parse_sep_cmd(struct token_stream *stream, struct cmd **out, struct cmd *left);
bool parser_parse_cmd_line_2(struct token_stream *stream, struct cmd **out);

bool parser_parse_job(struct token_stream *stream, struct cmd **out);
bool parser_parse_job_1(struct token_stream *stream, struct cmd **out, struct cmd *left);
bool parser_parse_pipe_cmd(struct token_stream *stream, struct cmd **out, struct cmd *left);

bool parser_parse_cmd(struct token_stream *stream, struct cmd **out);
bool parser_parse_simple_cmd(struct token_stream *stream, struct cmd **out, struct vector *redirects);
bool parser_parse_arg_list(struct token_stream *stream, struct cmd **out, struct simple_cmd *left);

bool parser_parse_redirect(struct token_stream *stream, struct cmd **out);
bool parser_parse_redirect_list(struct token_stream *stream, struct vector **out, struct vector *left);

bool parser_parse_left_cmd(struct token_stream *stream, struct cmd **out);
bool parser_parse_right_cmd(struct token_stream *stream, struct cmd **out);
bool parser_parse_right_append_cmd(struct token_stream *stream, struct cmd **out);

bool parser_parse(struct token_stream *stream, struct cmd **out)
{
    if (!parser_parse_cmd_line(stream, out))
        return false;

    if (token_get_type(token_stream_lookahead(stream)) != TOKEN_T_EOF)
    {
        *out = NULL;
        return false;
    }

    return true;
}

bool parser_parse_cmd_line(struct token_stream *stream, struct cmd **out)
{
    *out = NULL;

    int token_t = token_get_type(token_stream_lookahead(stream));

    if (token_t == TOKEN_T_EOF)
        return true;

    if (token_t != TOKEN_T_STR && token_t != TOKEN_T_LEFT &&
        token_t != TOKEN_T_RIGHT && token_t != TOKEN_T_RIGHT_APPEND)
        return false;

    struct cmd *job;
    if (!parser_parse_job(stream, &job))
        return false;

    return parser_parse_cmd_line_1(stream, out, job);
}

bool parser_parse_cmd_line_1(struct token_stream *stream, struct cmd **out, struct cmd *left)
{
    int token_t = token_get_type(token_stream_lookahead(stream));

    if (token_t == TOKEN_T_SEMICOLON)
        return parser_parse_sep_cmd(stream, out, left);

    if (token_t == TOKEN_T_BG)
        return parser_parse_bg_cmd(stream, out, left);

    if (token_t == TOKEN_T_EOF)
    {
        *out = left;
        return true;
    }

    *out = NULL;
    return false;
}

bool parser_parse_sep_cmd(struct token_stream *stream, struct cmd **out, struct cmd *left)
{
    token_stream_next(stream);

    struct cmd *right;
    if (!parser_parse_cmd_line(stream, &right))
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

bool parser_parse_bg_cmd(struct token_stream *stream, struct cmd **out, struct cmd *left)
{
    token_stream_next(stream);

    struct cmd *right;
    if (!parser_parse_cmd_line(stream, &right))
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

bool parser_parse_job(struct token_stream *stream, struct cmd **out)
{
    int token_t = token_get_type(token_stream_lookahead(stream));

    *out = NULL;

    if (token_t != TOKEN_T_STR && token_t != TOKEN_T_LEFT &&
        token_t != TOKEN_T_RIGHT && token_t != TOKEN_T_RIGHT_APPEND)
        return false;

    struct cmd *cmd;
    if (!parser_parse_cmd(stream, &cmd))
        return false;

    return parser_parse_job_1(stream, out, cmd);
}

bool parser_parse_job_1(struct token_stream *stream, struct cmd **out, struct cmd *left)
{
    int token_t = token_get_type(token_stream_lookahead(stream));

    if (token_t == TOKEN_T_PIPE)
        return parser_parse_pipe_cmd(stream, out, left);

    if (token_t == TOKEN_T_SEMICOLON || token_t == TOKEN_T_BG || token_t == TOKEN_T_EOF)
    {
        *out = left;
        return true;
    }

    *out = NULL;
    return false;
}

bool parser_parse_pipe_cmd(struct token_stream *stream, struct cmd **out, struct cmd *left)
{
    token_stream_next(stream);

    struct cmd *right;
    if (!parser_parse_cmd(stream, &right))
        return false;

    struct pipe_cmd *pipe_cmd = pipe_cmd_init();
    pipe_cmd_set_left(pipe_cmd, left);
    pipe_cmd_set_right(pipe_cmd, right);

    return parser_parse_job_1(stream, out, (struct cmd *)pipe_cmd);
}

bool parser_parse_cmd(struct token_stream *stream, struct cmd **out)
{
    *out = NULL;

    int token_type = token_get_type(token_stream_lookahead(stream));

    if (token_type != TOKEN_T_STR && token_type != TOKEN_T_LEFT &&
        token_type != TOKEN_T_RIGHT && token_type != TOKEN_T_RIGHT_APPEND)
        return false;

    struct vector *redirects;
    if (!parser_parse_redirect_list(stream, &redirects, vector_init()))
        return false;

    token_type = token_get_type(token_stream_lookahead(stream));

    if (token_type != TOKEN_T_STR)
        return false;

    struct cmd *cmd;
    if (!parser_parse_simple_cmd(stream, &cmd, redirects))
        return false;

    return parser_parse_arg_list(stream, out, (struct simple_cmd *)cmd);
}

bool parser_parse_simple_cmd(struct token_stream *stream, struct cmd **out, struct vector *redirects)
{
    char *token_lex = token_get_lex(token_stream_lookahead(stream));

    struct simple_cmd *simple_cmd;
    if (strcmp(token_lex, "cd") == 0)
        simple_cmd = (struct simple_cmd *)cd_cmd_init();
    else
        simple_cmd = simple_cmd_init(token_lex);

    token_stream_next(stream);

    for (int i = 0; i < vector_count(redirects); i++)
        simple_cmd_add_redirect(simple_cmd, (struct cmd *)vector_get(redirects, i));

    *out = (struct cmd *)simple_cmd;
    return true;
}

bool parser_parse_arg_list(struct token_stream *stream, struct cmd **out, struct simple_cmd *left)
{
    int token_t = token_get_type(token_stream_lookahead(stream));

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
        if (!parser_parse_redirect(stream, &redirect))
            return false;

        simple_cmd_add_redirect(left, redirect);
        return parser_parse_arg_list(stream, out, left);
    }

    if (token_t == TOKEN_T_STR)
    {
        simple_cmd_add_arg(left, token_get_lex(token_stream_lookahead(stream)));
        token_stream_next(stream);
        return parser_parse_arg_list(stream, out, left);
    }

    return false;
}

bool parser_parse_redirect_list(struct token_stream *stream, struct vector **out, struct vector *left)
{
    int token_t = token_get_type(token_stream_lookahead(stream));

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
        if (!parser_parse_redirect(stream, &redirect))
            return false;

        vector_add(left, redirect);
        return parser_parse_redirect_list(stream, out, left);
    }

    return false;
}

bool parser_parse_redirect(struct token_stream *stream, struct cmd **out)
{
    int token_type = token_get_type(token_stream_lookahead(stream));

    if (token_type == TOKEN_T_LEFT)
        return parser_parse_left_cmd(stream, out);

    if (token_type == TOKEN_T_RIGHT)
        return parser_parse_right_cmd(stream, out);

    if (token_type == TOKEN_T_RIGHT_APPEND)
        return parser_parse_right_append_cmd(stream, out);

    *out = NULL;
    return false;
}

bool parser_parse_left_cmd(struct token_stream *stream, struct cmd **out)
{
    token_stream_next(stream);

    struct token *token = token_stream_lookahead(stream);
    if (token_get_type(token) != TOKEN_T_STR)
    {
        *out = NULL;
        return false;
    }

    *out = (struct cmd *)left_cmd_init(token_get_lex(token));
    token_stream_next(stream);
    return true;
}

bool parser_parse_right_cmd(struct token_stream *stream, struct cmd **out)
{
    token_stream_next(stream);

    struct token *token = token_stream_lookahead(stream);
    if (token_get_type(token) != TOKEN_T_STR)
    {
        *out = NULL;
        return false;
    }

    *out = (struct cmd *)right_cmd_init(token_get_lex(token));
    token_stream_next(stream);
    return true;
}

bool parser_parse_right_append_cmd(struct token_stream *stream, struct cmd **out)
{
    token_stream_next(stream);

    struct token *token = token_stream_lookahead(stream);
    if (token_get_type(token) != TOKEN_T_STR)
    {
        *out = NULL;
        return false;
    }

    *out = (struct cmd *)right_append_cmd_init(token_get_lex(token));
    token_stream_next(stream);
    return true;
}