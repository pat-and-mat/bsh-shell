#include <stdlib.h>
#include <string.h>

#include <utils/vector.h>
#include <compiler/tokenizer.h>
#include <compiler/token.h>

int tokenizer_get_token_type(char *lex);

void tokenizer_init(struct tokenizer *t, char *text)
{
    t->text = malloc(sizeof(char) * (strlen(text) + 1));
    strcpy(t->text, text);
    t->tokens = malloc(sizeof(struct vector));
    vector_init(t->tokens);
    t->makes_history = 1;
}

void tokenizer_free(struct tokenizer *t, char *text)
{
    free(t->text);
    vector_free(t->tokens);
    free(t->tokens);
}

char *tokenizer_get_text(struct tokenizer *t)
{
    return t->text;
}

struct vector *tokenizer_get_tokens(struct tokenizer *t)
{
    return t->tokens;
}

int tokenizer_get_makes_history(struct tokenizer *t)
{
    return t->makes_history;
}

void tokenizer_tokenize(struct tokenizer *t)
{
    t->makes_history = 1;

    t->tokens = malloc(sizeof(struct vector));
    char *delim; /* Points to first space delimiter */

    t->text[strlen(t->text) - 1] = ' '; /* Replace trailing ’\n’ with space */
    if (*t->text && (*t->text == ' '))
    {
        t->makes_history = 0;
        while (*t->text && (*t->text == ' ')) /* Ignore leading spaces */
            t->text++;
    }

    struct token token;
    /* Build the argv list */
    while ((delim = strchr(t->text, ' ')))
    {
        *delim = '\0';

        token_init(&token, tokenizer_get_token_type(t->text), "$");
        vector_add(t->tokens, &token, sizeof(struct token));

        t->text = delim + 1;
        while (*t->text && (*t->text == ' ')) /* Ignore spaces */
            t->text++;
    }

    token_init(&token, TOKEN_T_EOF, "$");
    vector_add(t->tokens, &token, sizeof(struct token));
}

int tokenizer_get_token_type(char *lex)
{
    return TOKEN_T_STR;
}
