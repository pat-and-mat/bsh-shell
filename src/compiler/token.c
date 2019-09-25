#include <string.h>

#include <utils/xmemory.h>
#include <compiler/token.h>

void token_init(struct token *t, int type, char *lex)
{
    t->type = type;
    t->lex = xstring(lex);
}

void token_free(struct token *t)
{
    xfree(t->lex);
}

int token_get_type(struct token *t)
{
    return t->type;
}

char *token_get_lex(struct token *t)
{
    return t->lex;
}