#ifndef TOKEN_H
#define TOKEN_H

#define TOKEN_T_EOF -1
#define TOKEN_T_STR 1

struct token
{
    int type;
    char *lex;
};

void token_init(struct token *t, int type, char *lex);
void token_free(struct token *t);
int token_get_type(struct token *t);
char *token_get_lex(struct token *t);

#endif