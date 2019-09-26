#include <string.h>
#include <stdlib.h>

#include <compiler/token.h>
#include <utils/xmemory.h>

struct token *token_init(int type, char *lex)
{
    struct token *t = xmalloc(sizeof(struct token));
    token_init_allocated(t, type, lex);
    return t;
}

void token_init_allocated(struct token *t, int type, char *lex)
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