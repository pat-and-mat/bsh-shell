#include <stdlib.h>
#include <string.h>

#include <utils/vector.h>
#include <utils/xmemory.h>
#include <compiler/tokenizer.h>
#include <compiler/token.h>

int tokenizer_get_token_type(char *lex);

void tokenizer_init(struct tokenizer *t, char *text)
{
    t->text = xmalloc(sizeof(char) * (strlen(text) + 1));
    strcpy(t->text, text);
    t->tokens = xmalloc(sizeof(struct vector));
    vector_init(t->tokens);
    t->makes_history = 1;
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
    char text_mem[strlen(t->text) + 1];
    char *text = text_mem;
    strcpy(text, t->text);
    char *delim; /* Points to first space delimiter */

    if (text[strlen(text) - 1] == '\n')
        text[strlen(text) - 1] = ' '; /* Replace trailing ’\n’ with space */

    if (*text && (*text == ' '))
    {
        t->makes_history = 0;
        while (*text && (*text == ' ')) /* Ignore leading spaces */
            text++;
    }

    struct token *token;
    /* Build the argv list */
    while ((delim = strchr(text, ' ')))
    {
        *delim = '\0';

        token = xmalloc(sizeof(struct token));
        token_init(token, tokenizer_get_token_type(text), text);
        vector_add(t->tokens, token);

        text = delim + 1;
        while (*text && (*text == ' ')) /* Ignore spaces */
            text++;
    }

    token = xmalloc(sizeof(struct token));
    token_init(token, TOKEN_T_EOF, "$");
    vector_add(t->tokens, token);
}

int tokenizer_get_token_type(char *lex)
{
    return TOKEN_T_STR;
}
