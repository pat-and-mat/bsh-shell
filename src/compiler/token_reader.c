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
}