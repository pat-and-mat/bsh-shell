#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <signal.h>

#include <shell/minimalistic_prompt.h>
#include <shell/history.h>
#include <shell/jobs.h>
#include <compiler/text_stream.h>
#include <compiler/token_stream.h>
#include <compiler/preprocessor.h>
#include <compiler/tokenizer.h>
#include <compiler/parser.h>
#include <cmds/cmd.h>
#include <utils/xmemory.h>
#include <utils/colors.h>
#include <utils/sighandlers.h>

void open_session();
void close_session();

int main(int argc, char *argv[])
{
    open_session();

    bool last_cmd_status = true;

    char *line;
    size_t len;

    while (true)
    {
        line = NULL;
        len = 0;

        print_minimalistic_prompt(last_cmd_status);

        getline(&line, &len, stdin);
        xmem_add_manually_allocated(line);
        if (strlen(line) == 0)
        {
            bg_clean_all();
            printf("exit\n");
            break;
        }

        struct text_stream *text_stream;
        struct token_stream *token_stream;
        struct cmd *cmd;

        if (!preprocessor_preprocess(text_stream_init(line), &text_stream))
            fprintf(stderr, "Preprocessing failed\n");
        else if (!tokenizer_tokenize(text_stream, &token_stream))
            fprintf(stderr, "Lexical analysis failed\n");
        else if (!parser_parse(token_stream, &cmd))
            fprintf(stderr, "Syntax analysis failed\n");
        else if (cmd != NULL)
        {
            printf("%sbsh> %s", build_fg_color(COLOR_GREEN), COLOR_RESET);
            cmd_print(cmd);
            printf("\n");

            last_cmd_status = cmd_run(cmd, true);
        }

        bg_clean_finished();
    }

    close_session();
    return 0;
}

void open_session()
{
    xmem_init();
    history_init("/tmp/bsh_history");
    history_load();
    bg_init();

    // Ignore Ctrl + Z
    signal(SIGTSTP, sigstp_handler);
    // Ignore Ctrl + C
    signal(SIGINT, sigint_handler);
    // Ignore Ctrl + /
    signal(SIGQUIT, sigquit_handler);
}

void close_session()
{
    history_save();
    xmem_free();
}