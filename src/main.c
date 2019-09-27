#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <compiler/tokenizer.h>
#include <compiler/parser.h>
#include <cmds/cmd.h>
#include <utils/xmemory.h>

int main(int argc, char *argv[])
{
    char *line;
    size_t len;

    while (true)
    {
        xmem_init();

        line = NULL;
        len = 0;

        printf("$ ");
        getline(&line, &len, stdin);

        struct tokenizer *tokenizer = tokenizer_init(line);
        tokenizer_tokenize(tokenizer);

        struct vector *tokens = tokenizer_get_tokens(tokenizer);

        struct parser *parser = parser_init(tokens);

        if (!parser_parse(parser))
        {
            printf("Parsing error\n");
            xmem_free();
            continue;
        }

        struct cmd *cmd = parser_get_cmd(parser);
        cmd_run(cmd);

        free(line);
        xmem_free();
    }

    return 0;
}