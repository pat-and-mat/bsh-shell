#ifndef TOKEN_H
#define TOKEN_H

#define TOKEN_T_STR 1

struct token
{
    int type;
    const char *lex;
};

void token_init(struct token *t, int type, const char *lex);
int token_get_type(struct token *t);
const char *token_get_lex(struct token *t);

#endif