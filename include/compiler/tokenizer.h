#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <stdbool.h>

struct token_stream;
struct text_reader;

bool tokenizer_tokenize(struct text_reader *reader, struct token_stream **out);

#endif