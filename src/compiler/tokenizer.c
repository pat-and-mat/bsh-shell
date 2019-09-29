#include <stdlib.h>
#include <string.h>

#include <utils/vector.h>
#include <utils/xmemory.h>
#include <compiler/tokenizer.h>
#include <compiler/token.h>
#include <compiler/text_reader.h>
#include <compiler/token_stream.h>

int tokenizer_get_token_type(char *lex);

bool tokenizer_tokenize(struct text_reader *t, struct token_stream **out)
{
    struct vector *tokens = vector_init();
    char text_mem[strlen(t->text) + 1];
    char *text = text_mem;
    strcpy(text, t->text);
    char *delim; /* Points to first space delimiter */

    if (text[strlen(text) - 1] == '\n')
        text[strlen(text) - 1] = ' '; /* Replace trailing ’\n’ with space */

    while (*text && (*text == ' ')) /* Ignore leading spaces */
        text++;

    struct token *token;
    while ((delim = strchr(text, ' ')))
    {
        *delim = '\0';

        vector_add(tokens, token_init(tokenizer_get_token_type(text), text));

        text = delim + 1;
        while (*text && (*text == ' ')) /* Ignore spaces */
            text++;
    }

    vector_add(tokens, token_init(TOKEN_T_EOF, "$"));

    *out = token_stream_init(tokens);
    return true;
}

int tokenizer_get_token_type(char *lex)
{
    if (strcmp(lex, ";") == 0)
        return TOKEN_T_SEMICOLON;

    if (strcmp(lex, "|") == 0)
        return TOKEN_T_PIPE;

    if (strcmp(lex, "<") == 0)
        return TOKEN_T_LEFT;

    if (strcmp(lex, ">") == 0)
        return TOKEN_T_RIGHT;

    if (strcmp(lex, ">>") == 0)
        return TOKEN_T_RIGHT_APPEND;

    if (strcmp(lex, "&") == 0)
        return TOKEN_T_BG;

    return TOKEN_T_STR;
}
