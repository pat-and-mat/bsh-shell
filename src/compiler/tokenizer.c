#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include <utils/vector.h>
#include <utils/xmemory.h>
#include <compiler/tokenizer.h>
#include <compiler/token.h>
#include <compiler/text_stream.h>
#include <compiler/token_stream.h>

#define STATE_ERROR -1
#define STATE_DONE -2

#define STATE_START 0
#define STATE_EOF 1
#define STATE_SPACE 2
#define STATE_SEMICOLON 3
#define STATE_BG 4
#define STATE_PIPE 5
#define STATE_LEFT 6
#define STATE_RIGHT 7
#define STATE_RIGHT_APPEND 8
#define STATE_ALNUM 9
#define STATE_SCAPE_CHAR 10
#define STATE_OQUOTE 11
#define STATE_CQUOTE 12
#define STATE_QUOTED 13

#define MAX_STATE 13

int tokenizer_state_start(struct text_stream *t, struct vector *tokens);
int tokenizer_state_eof(struct text_stream *t, struct vector *tokens);
int tokenizer_state_space(struct text_stream *t, struct vector *tokens);
int tokenizer_state_semicolon(struct text_stream *t, struct vector *tokens);
int tokenizer_state_bg(struct text_stream *t, struct vector *tokens);
int tokenizer_state_pipe(struct text_stream *t, struct vector *tokens);
int tokenizer_state_left(struct text_stream *t, struct vector *tokens);
int tokenizer_state_right(struct text_stream *t, struct vector *tokens);
int tokenizer_state_right_append(struct text_stream *t, struct vector *tokens);
int tokenizer_state_alnum(struct text_stream *t, struct vector *tokens);
int tokenizer_state_scape_char(struct text_stream *t, struct vector *tokens);
int tokenizer_state_oquote(struct text_stream *t, struct vector *tokens);
int tokenizer_state_cquote(struct text_stream *t, struct vector *tokens);
int tokenizer_state_quoted(struct text_stream *t, struct vector *tokens);

int (*states[MAX_STATE + 1])(struct text_stream *, struct vector *);

void states_init()
{
    states[STATE_START] = tokenizer_state_start;
    states[STATE_EOF] = tokenizer_state_eof;
    states[STATE_SPACE] = tokenizer_state_space;
    states[STATE_SEMICOLON] = tokenizer_state_semicolon;
    states[STATE_BG] = tokenizer_state_bg;
    states[STATE_PIPE] = tokenizer_state_pipe;
    states[STATE_LEFT] = tokenizer_state_left;
    states[STATE_RIGHT] = tokenizer_state_right;
    states[STATE_RIGHT_APPEND] = tokenizer_state_right_append;
    states[STATE_ALNUM] = tokenizer_state_alnum;
    states[STATE_SCAPE_CHAR] = tokenizer_state_scape_char;
    states[STATE_OQUOTE] = tokenizer_state_oquote;
    states[STATE_CQUOTE] = tokenizer_state_cquote;
    states[STATE_QUOTED] = tokenizer_state_quoted;
}

bool tokenizer_tokenize(struct text_stream *t, struct token_stream **out)
{
    states_init();
    struct vector *tokens = vector_init();

    int state = STATE_START;
    while (state != STATE_ERROR && state != STATE_DONE)
        state = (*states[state])(t, tokens);

    *out = NULL;
    if (state == STATE_ERROR)
        return false;

    *out = token_stream_init(tokens);
    return true;
}

int tokenizer_state_start(struct text_stream *t, struct vector *tokens)
{
    char c = text_stream_lookahead(t);
    int state = STATE_ERROR;

    if (c == TEXT_STREAM_EOF)
        state = STATE_EOF;
    if (c == ' ')
        state = STATE_SPACE;
    if (c == ';')
        state = STATE_SEMICOLON;
    if (c == '&')
        state = STATE_BG;
    if (c == '|')
        state = STATE_PIPE;
    if (c == '<')
        state = STATE_LEFT;
    if (c == '>')
        state = STATE_RIGHT;
    if (c == '"')
        state = STATE_OQUOTE;
    if (c == '\\')
        state = STATE_SCAPE_CHAR;
    if (isalnum(c))
        state = STATE_ALNUM;

    text_stream_next(t);
    return state;
}

int tokenizer_state_eof(struct text_stream *t, struct vector *tokens)
{
    vector_add(tokens, token_init(TOKEN_T_EOF, "$"));
    return STATE_DONE;
}

int tokenizer_state_space(struct text_stream *t, struct vector *tokens)
{
    char c = text_stream_lookahead(t);

    if (c == ' ')
    {
        text_stream_next(t);
        return STATE_SPACE;
    }

    text_stream_recognize(t);
    return STATE_START;
}

int tokenizer_state_semicolon(struct text_stream *t, struct vector *tokens)
{
    char *lex = text_stream_recognize(t);
    vector_add(tokens, token_init(TOKEN_T_SEMICOLON, lex));
    return STATE_START;
}

int tokenizer_state_bg(struct text_stream *t, struct vector *tokens)
{
    char *lex = text_stream_recognize(t);
    vector_add(tokens, token_init(TOKEN_T_BG, lex));
    return STATE_START;
}

int tokenizer_state_pipe(struct text_stream *t, struct vector *tokens)
{
    char *lex = text_stream_recognize(t);
    vector_add(tokens, token_init(TOKEN_T_PIPE, lex));
    return STATE_START;
}

int tokenizer_state_left(struct text_stream *t, struct vector *tokens)
{
    char *lex = text_stream_recognize(t);
    vector_add(tokens, token_init(TOKEN_T_LEFT, lex));
    return STATE_START;
}

int tokenizer_state_right(struct text_stream *t, struct vector *tokens)
{
    char c = text_stream_lookahead(t);

    if (c == '>')
    {
        text_stream_next(t);
        return STATE_RIGHT_APPEND;
    }

    char *lex = text_stream_recognize(t);
    vector_add(tokens, token_init(TOKEN_T_RIGHT, lex));
    return STATE_START;
}

int tokenizer_state_right_append(struct text_stream *t, struct vector *tokens)
{
    char *lex = text_stream_recognize(t);
    vector_add(tokens, token_init(TOKEN_T_RIGHT_APPEND, lex));
    return STATE_START;
}

int tokenizer_state_alnum(struct text_stream *t, struct vector *tokens)
{
    char c = text_stream_lookahead(t);

    if (isalnum(c))
    {
        text_stream_next(t);
        return STATE_ALNUM;
    }

    char *lex = text_stream_recognize(t);
    vector_add(tokens, token_init(TOKEN_T_STR, lex));
    return STATE_START;
}

int tokenizer_state_scape_char(struct text_stream *t, struct vector *tokens)
{
    char c = text_stream_lookahead(t);
    if (c == TEXT_STREAM_EOF)
        return STATE_ERROR;

    text_stream_next(t);
    return STATE_ALNUM;
}

int tokenizer_state_oquote(struct text_stream *t, struct vector *tokens)
{
    char c = text_stream_lookahead(t);
    if (c == TEXT_STREAM_EOF)
        return STATE_ERROR;

    text_stream_next(t);
    return STATE_QUOTED;
}

int tokenizer_state_cquote(struct text_stream *t, struct vector *tokens)
{
    char *lex = text_stream_recognize(t);
    vector_add(tokens, token_init(TOKEN_T_STR, lex));
    return STATE_START;
}

int tokenizer_state_quoted(struct text_stream *t, struct vector *tokens)
{
    char c = text_stream_lookahead(t);

    if (c == TEXT_STREAM_EOF)
        return STATE_ERROR;

    if (c == '"')
    {
        text_stream_next(t);
        return STATE_CQUOTE;
    }

    text_stream_next(t);
    return STATE_QUOTED;
}
