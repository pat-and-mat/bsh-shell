#include <compiler/token_stream.h>
#include <utils/vector.h>
#include <utils/xmemory.h>

struct token_stream *token_stream_init(struct vector *tokens)
{
    struct token_stream *token_stream = xmalloc(sizeof(struct token_stream));
    token_stream_init_allocated(token_stream, tokens);
    return token_stream;
}

void token_stream_init_allocated(struct token_stream *stream, struct vector *tokens)
{
    stream->i = 0;
    stream->tokens = tokens;
}

struct token *token_stream_lookahead(struct token_stream *stream)
{
    return vector_get(stream->tokens, stream->i);
}

void token_stream_next(struct token_stream *stream)
{
    stream->i++;
}

void token_stream_reset(struct token_stream *t)
{
    t->i = 0;
}
