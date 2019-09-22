#ifndef TOKEN_H
#define TOKEN_H

#define TOKEN_T_STR

struct token
{
    int type;
    const char *lex;
};

void token_init(struct token *t, int type, const char *lex);

#endif