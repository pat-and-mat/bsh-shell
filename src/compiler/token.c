#include <compiler/token.h>

void token_init(struct token *t, int type, const char *lex)
{
    t->type = type;
    t->lex = lex;
}

int token_get_type(struct token *t)
{
    return t->type;
}

const char *token_get_lex(struct token *t)
{
    return t->lex;
}