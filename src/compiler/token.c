#include <compiler/token.h>

void token_init(struct token *t, int type, const char *lex)
{
    t->type = type;
    t->lex = lex;
}
