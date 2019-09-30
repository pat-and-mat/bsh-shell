#include <compiler/preprocessor.h>
#include <compiler/text_stream.h>
#include <shell/history.h>

bool preprocessor_preprocess(struct text_stream *stream, struct text_stream **out)
{
    history_add(stream->text);
    *out = stream;
    return true;
}
