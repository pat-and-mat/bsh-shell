#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <compiler/preprocessor.h>
#include <compiler/text_stream.h>
#include <shell/history.h>
#include <utils/xmemory.h>

#define STATE_DONE -2
#define STATE_ERROR -1
#define STATE_START 0
#define STATE_EXC 1
#define STATE_EXC_1 2
#define STATE_IDX 3
#define STATE_OTHER 4
#define STATE_EOF 5
#define STATE_CMD 6

#define MAX_STATE 6

int preprocessor_state_start(struct text_stream *t, char **text, int *len);
int preprocessor_state_eof(struct text_stream *t, char **text, int *len);
int preprocessor_state_exc(struct text_stream *t, char **text, int *len);
int preprocessor_state_exc_1(struct text_stream *t, char **text, int *len);
int preprocessor_state_idx(struct text_stream *t, char **text, int *len);
int preprocessor_state_cmd(struct text_stream *t, char **text, int *len);
int preprocessor_state_other(struct text_stream *t, char **text, int *len);

int (*states[MAX_STATE + 1])(struct text_stream *t, char **text, int *len);

void str_expand(char **str, char *str1, int *len);

void preprocessor_states_init()
{
    states[STATE_START] = preprocessor_state_start;
    states[STATE_EXC] = preprocessor_state_exc;
    states[STATE_EXC_1] = preprocessor_state_exc_1;
    states[STATE_IDX] = preprocessor_state_idx;
    states[STATE_OTHER] = preprocessor_state_other;
    states[STATE_EOF] = preprocessor_state_eof;
    states[STATE_CMD] = preprocessor_state_cmd;
}

bool preprocessor_preprocess(struct text_stream *stream, struct text_stream **out)
{
    preprocessor_states_init();
    int len = strlen(stream->text);

    char *text = xmalloc(sizeof(char) * (len + 1));

    int state = STATE_START;
    while (state != STATE_ERROR && state != STATE_DONE)
        state = (*states[state])(stream, &text, &len);

    *out = NULL;
    if (state == STATE_ERROR)
        return false;

    if (len > 0 && text[0] != ' ')
    {
        char *to_save = xmalloc(sizeof(char) * (len + 1));
        strcpy(to_save, text);
        if (text[len - 1] == '\n')
            to_save[len - 1] = '\0';

        if (strlen(to_save) > 0)
            history_add(to_save);
    }

    *out = text_stream_init(text);
    return true;
}

int preprocessor_state_start(struct text_stream *t, char **text, int *len)
{
    char c = text_stream_lookahead(t);
    int state;
    if (c == '!')
        state = STATE_EXC;
    else if (c == TEXT_STREAM_EOF)
        state = STATE_EOF;
    else
        state = STATE_OTHER;

    text_stream_accept(t);
    text_stream_next(t);
    return state;
}

int preprocessor_state_eof(struct text_stream *t, char **text, int *len)
{
    str_expand(text, "\n", len);
    return STATE_DONE;
}

int preprocessor_state_exc(struct text_stream *t, char **text, int *len)
{
    char c = text_stream_lookahead(t);
    int state;

    if (c == TEXT_STREAM_EOF)
    {
        str_expand(text, text_stream_recognize(t), len);
        return STATE_START;
    }

    if (c == '!')
        state = STATE_EXC_1;
    else if (isdigit(c) || c == '-')
        state = STATE_IDX;
    else if (isalpha(c))
        state = STATE_CMD;
    else
        state = STATE_OTHER;

    text_stream_accept(t);
    text_stream_next(t);
    return state;
}

int preprocessor_state_exc_1(struct text_stream *t, char **text, int *len)
{
    text_stream_recognize(t);
    str_expand(text, history_last(), len);
    return STATE_START;
}

int preprocessor_state_idx(struct text_stream *t, char **text, int *len)
{
    char c = text_stream_lookahead(t);
    if (isdigit(c))
    {
        text_stream_accept(t);
        text_stream_next(t);
        return STATE_IDX;
    }

    char *indexer = text_stream_recognize(t);
    int idx = atoi(indexer + 1);
    if (idx < 0)
        idx = history_count() - idx;
    if (idx < 0 || idx >= history_count())
        return STATE_ERROR;

    str_expand(text, history_get(idx), len);
    return STATE_START;
}

int preprocessor_state_cmd(struct text_stream *t, char **text, int *len)
{
    char c = text_stream_lookahead(t);
    if (c != TEXT_STREAM_EOF && c != '!')
    {
        text_stream_accept(t);
        text_stream_next(t);
        return STATE_CMD;
    }

    char *cmd_indexer = text_stream_recognize(t);
    char *cmd = history_last_starting(cmd_indexer + 1);
    if (!cmd)
        return STATE_ERROR;

    str_expand(text, cmd, len);
    return STATE_START;
}

int preprocessor_state_other(struct text_stream *t, char **text, int *len)
{
    char c = text_stream_lookahead(t);
    if (c != TEXT_STREAM_EOF && c != '!')
    {
        text_stream_accept(t);
        text_stream_next(t);
        return STATE_OTHER;
    }

    char *other = text_stream_recognize(t);
    str_expand(text, other, len);
    return STATE_START;
}

void str_expand(char **str, char *str1, int *len)
{
    char *new_str = *str;
    if (strlen(*str) + strlen(str1) > *len)
        new_str = xrealloc(*str, strlen(*str) + strlen(str1) + 1);
    if (new_str)
        strcat(*str, str1);
    *str = new_str;
}
