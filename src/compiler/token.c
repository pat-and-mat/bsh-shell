#include <string.h>

#include <utils/xmemory.h>
#include <compiler/token.h>

void token_init(struct token *t, int type, char *lex)
{
    t->type = type;
    t->lex = xmalloc(sizeof(char) * (strlen(lex) + 1));
    strcpy(t->lex, lex);
}

int token_get_type(struct token *t)
{
    return t->type;
}

char *token_get_lex(struct token *t)
{
    return t->lex;
}