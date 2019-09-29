#include <compiler/preprocessor.h>
#include <compiler/text_stream.h>

bool preprocessor_preprocess(char *text, struct text_stream **out)
{
    *out = text_stream_init(text);
    return true;
}
