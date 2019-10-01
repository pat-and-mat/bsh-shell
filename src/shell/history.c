#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include <shell/history.h>
#include <utils/vector.h>
#include <utils/xmemory.h>

struct history
{
    char *file;
    struct vector *commands;
    int hist_n;
};

struct history history;

void history_init(char *filename)
{
    history.file = filename;
    history.hist_n = 500;
    history.commands = vector_init();
}

void history_set_histn(int histn)
{
    history.hist_n = histn;
}

void history_load()
{
    if (access(history.file, F_OK) == -1)
        return;

    FILE *hist_stream = fopen(history.file, "r");
    char *line = NULL;
    size_t len = 0;
    while (getline(&line, &len, hist_stream) != -1)
    {
        xmem_add_manually_allocated(line);
        if (strlen(line) > 0 && line[0] == '>')
        {
            if (line[strlen(line) - 1] == '\n')
                line[strlen(line) - 1] = '\0';
            history_add(line + 1);
        }
        line = NULL;
        len = 0;
    }

    fclose(hist_stream);
}

void history_save()
{
    FILE *hist_stream = fopen(history.file, "w");

    if (hist_stream)
    {
        for (int i = 0; i < vector_count(history.commands); i++)
            fprintf(hist_stream, ">%s\n", (char *)vector_get(history.commands, i));

        fclose(hist_stream);
    }
    else
        fprintf(stderr, "Could not save history\n");
}

void history_add(char *cmd_line)
{
    while (history_count() == history.hist_n)
        vector_delete(history.commands, 0);
    vector_add(history.commands, cmd_line);
}

int history_count()
{
    return vector_count(history.commands);
}

char *history_get(int i)
{
    if (i < 0 || i >= history_count())
        return NULL;
    return vector_get(history.commands, i);
}

char *history_last()
{
    return history_get(history_count() - 1);
}

bool match_preffix(char *preffix, char *str);
char *history_last_starting(char *preffix)
{
    char *cmd;
    for (int i = history_count() - 1; i >= 0; i--)
    {
        cmd = vector_get(history.commands, i);
        if (match_preffix(preffix, cmd))
            return cmd;
    }
    return NULL;
}

bool match_preffix(char *preffix, char *str)
{
    for (int i = 0; i < strlen(preffix); i++)
        if (str[i] != preffix[i])
            return false;
    return true;
}