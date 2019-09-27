#ifndef TOKEN_H
#define TOKEN_H

#define TOKEN_T_EOF -1
#define TOKEN_T_STR 1
#define TOKEN_T_SEMICOLON 2
#define TOKEN_T_PIPE 3
#define TOKEN_T_LEFT 4
#define TOKEN_T_RIGHT 5
#define TOKEN_T_RIGHT_APPEND 6
#define TOKEN_T_BG 7

struct token
{
    int type;
    char *lex;
};

struct token *token_init(int type, char *lex);
void token_init_allocated(struct token *t, int type, char *lex);
int token_get_type(struct token *t);
char *token_get_lex(struct token *t);

#endif