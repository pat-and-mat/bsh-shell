#ifndef TEXT_STREAM_H
#define TEXT_STREAM_H

#include <stdbool.h>

#define TEXT_STREAM_EOF '\n'

struct text_stream
{
    char *text;
    char *lookahead;
    char *current;
};

struct text_stream *text_stream_init(char *text);
void text_stream_init_allocated(struct text_stream *t, char *text);
char text_stream_lookahead(struct text_stream *t);
void text_stream_next(struct text_stream *t);
void text_stream_accept(struct text_stream *t);
char *text_stream_recognize(struct text_stream *t);

#endif