#include <string.h>
#include <compiler/preprocessor.h>
#include <compiler/text_stream.h>
#include <shell/history.h>
#include <utils/xmemory.h>

bool preprocessor_preprocess(struct text_stream *stream, struct text_stream **out)
{
    int len = strlen(stream->text);
    char *line = xmalloc(sizeof(char) * (len + 1));
    if (stream->text[len - 1] == '\n')
    {
        strcpy(line, stream->text);
        line[len - 1] = '\0';
    }

    history_add(line);
    *out = stream;
    return true;
}
