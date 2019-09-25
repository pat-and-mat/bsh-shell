#include <string.h>
#include <stdlib.h>

#include <compiler/token.h>
#include <utils/strutils.h>

void token_init(struct token *t, int type, char *lex)
{
    t->type = type;
    t->lex = malloc(sizeof(char) * (strlen(lex) + 1));
    strcpy(t->lex, lex);
}

void token_free(struct token *t)
{
    free(t->lex);
}

struct token *token_copy(struct token *t)
{
    struct token *cpy = malloc(sizeof(struct token));
    cpy->type = t->type;
    cpy->lex = str_copy(t->lex);
    return cpy;
}

int token_get_type(struct token *t)
{
    return t->type;
}

char *token_get_lex(struct token *t)
{
    return t->lex;
}