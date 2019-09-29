#ifndef PARSER_H
#define PARSER_H

#include <stdbool.h>

struct token_stream;
struct cmd;

bool parser_parse(struct token_stream *stream, struct cmd **out);

#endif