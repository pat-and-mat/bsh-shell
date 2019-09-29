#ifndef PREPROCESSOR_H
#define PREPROCESSOR_H

#include <stdbool.h>

struct text_stream;

bool preprocessor_preprocess(struct text_stream *stream, struct text_stream **out);

#endif