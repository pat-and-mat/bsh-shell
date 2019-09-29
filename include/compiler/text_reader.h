#ifndef TEXT_READER_H
#define TEXT_READER_H

#include <stdbool.h>

#define TEXT_READER_EOF '\n'

struct text_reader
{
    char *text;
    char *lookahead;
    char *start;
};

struct text_reader *text_reader_init(char *text);
void text_reader_init_allocated(struct text_reader *t, char *text);
char text_reader_lookahead(struct text_reader *t);
void text_reader_next(struct text_reader *t);
char *text_reader_recognize(struct text_reader *t);

#endif