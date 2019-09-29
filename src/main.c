#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include <shell/prompt.h>
#include <compiler/text_stream.h>
#include <compiler/token_stream.h>
#include <compiler/preprocessor.h>
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

        print_prompt();

        getline(&line, &len, stdin);
        xmem_add_manually_allocated(line);

        struct text_stream *text_stream;
        struct token_stream *token_stream;
        struct cmd *cmd;

        if (!preprocessor_preprocess(text_stream_init(line), &text_stream))
            printf("Preprocessing failed");
        else if (!tokenizer_tokenize(text_stream, &token_stream))
            printf("Lexical analysis failed\n");
        else if (!parser_parse(token_stream, &cmd))
            printf("Syntax analysis failed\n");
        else if (cmd != NULL)
        {
            cmd_print(cmd);
            printf("\n");
        }

        xmem_free();
    }

    return 0;
}