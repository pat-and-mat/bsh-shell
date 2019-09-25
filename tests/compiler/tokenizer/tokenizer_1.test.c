#include <string.h>
#include <stdio.h>

#include <compiler/token.h>
#include <compiler/tokenizer.h>
#include <utils/vector.h>

int main()
{

    char *text = "ls -l\n";

    struct token tokens_res[] = {{.type = TOKEN_T_STR, .lex = "ls"},
                                 {.type = TOKEN_T_STR, .lex = "-l"},
                                 {.type = TOKEN_T_EOF, .lex = "$"}};

    int makes_history = 1;

    struct tokenizer t;
    tokenizer_init(&t, text);

    tokenizer_tokenize(&t);

    tokenizer_free(&t);
    return 0;

    struct vector *tokens = tokenizer_get_tokens(&t);

    struct token *token;
    for (int i = 0; i < vector_count(tokens); i++)
    {
        token = vector_get(tokens, i);
        if (token->type != tokens_res[i].type || strcmp(token->lex, tokens_res[i].lex) != 0)
            return -1;
    }

    if (tokenizer_get_makes_history(&t) != makes_history)
        return -1;

    tokenizer_free(&t);
    return 0;
}