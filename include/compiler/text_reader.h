#ifndef TEXT_READER_H
#define TEXT_READER_H

struct text_reader
{
    char *text;
};

struct text_reader *text_reader_init(char *text);
void text_reader_init_allocated(struct text_reader *t, char *text);

#endif