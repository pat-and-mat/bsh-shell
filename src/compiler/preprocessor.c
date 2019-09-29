#include <compiler/preprocessor.h>
#include <compiler/text_stream.h>

bool preprocessor_preprocess(struct text_stream *stream, struct text_stream **out)
{
    *out = stream;
    return true;
}
