#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <stdbool.h>

struct token_stream;
struct text_stream;

bool tokenizer_tokenize(struct text_stream *reader, struct token_stream **out);

#endif