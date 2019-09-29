#include <string.h>

#include <utils/xmemory.h>
#include <compiler/text_reader.h>

struct text_reader *text_reader_init(char *text)
{
    struct text_reader *t = xmalloc(sizeof(struct text_reader));
    text_reader_init_allocated(t, text);
    return t;
}

void text_reader_init_allocated(struct text_reader *t, char *text)
{
    t->text = text;
    t->start = t->text;
    t->lookahead = t->text;
}

char text_reader_lookahead(struct text_reader *t)
{
    return *(t->lookahead);
}

void text_reader_next(struct text_reader *t)
{
    t->lookahead++;
}

char *text_reader_recognize(struct text_reader *t)
{
    int len = t->lookahead - t->start;
    char *lex = xmalloc(sizeof(char) * (len + 1));
    strncpy(lex, t->start, len);
    lex[len] = '\0';
    t->start = t->lookahead;
    return lex;
}