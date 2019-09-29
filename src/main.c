#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <compiler/text_reader.h>
#include <compiler/token_stream.h>
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

        struct token_stream *token_stream;
        struct cmd *cmd;

        if (!tokenizer_tokenize(text_reader_init(line), &token_stream))
            printf("Lexical analysis failed\n");
        else if (!parser_parse(token_stream, &cmd))
            printf("Syntax analysis failed\n");
        else
        {
            cmd_print(cmd);
            printf("\n");
        }

        free(line);
        xmem_free();
    }

    return 0;
}