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
    t->lookahead = t->text;
    t->current = xmalloc(sizeof(char) * strlen(text));
    t->current[0] = '\0';
}

char text_stream_lookahead(struct text_stream *t)
{
    return *(t->lookahead);
}

void text_stream_next(struct text_stream *t)
{
    t->lookahead++;
}

void text_stream_accept(struct text_stream *t)
{
    int len = strlen(t->current);
    t->current[len] = text_stream_lookahead(t);
    t->current[len + 1] = '\0';
}

char *text_stream_recognize(struct text_stream *t)
{
    int len = strlen(t->current);
    char *lex = xmalloc(sizeof(char) * (len + 1));
    strcpy(lex, t->current);
    t->current[0] = '\0';
    return lex;
}