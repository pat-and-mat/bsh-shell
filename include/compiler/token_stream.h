#ifndef TOKEN_STREAM_H
#define TOKEN_STREAM_H

struct vector;

struct token_stream
{
    struct vector *tokens;
    int i;
};

struct token_stream *token_stream_init(struct vector *tokens);
void token_stream_init_allocated(struct token_stream *stream, struct vector *tokens);
struct token *token_stream_lookahead(struct token_stream *stream);
void token_stream_next(struct token_stream *stream);
void token_stream_reset(struct token_stream *stream);

#endif