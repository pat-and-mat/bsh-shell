#include <string.h>

#include <utils/xmemory.h>
#include <compiler/text_stream.h>

struct text_stream *text_stream_init(char *text)
{
    struct text_stream *t = xmalloc(sizeof(struct text_stream));
    text_stream_init_allocated(t, text);
    return t;
}

void text_stream_init_allocated(struct text_stream *t, char *text)
{
    t->text = text;
    t->start = t->text;
    t->lookahead = t->text;
}

char text_stream_lookahead(struct text_stream *t)
{
    return *(t->lookahead);
}

void text_stream_next(struct text_stream *t)
{
    t->lookahead++;
}

char *text_stream_recognize(struct text_stream *t)
{
    int len = t->lookahead - t->start;
    char *lex = xmalloc(sizeof(char) * (len + 1));
    strncpy(lex, t->start, len);
    lex[len] = '\0';
    t->start = t->lookahead;
    return lex;
}