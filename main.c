#include <stdio.h>
#include "string_utils.h"

void process_cmd(char *cmd)
{
    int parts_len = 0;
    char **parts = split_string(cmd, "DELIM", &parts_len);
    printf("Parts: %d\n", parts_len);
    for (int i = 0; i < parts_len; i++)
    {
        printf("Part %d:%s", i, parts[i]);
    }
    // Free the memory allocated for the parts
    for (int i = 0; i < parts_len; i++)
    {
        free(parts[i]);
    }
    free(parts);
}

int main()
{
    char *dir = "/";
    while (1)
    {
        char *cmd = NULL;
        size_t len = 0;
        printf("~ %s ", dir);
        getline(&cmd, &len, stdin);
        string_strip(cmd);
        process_cmd(cmd);
    }
    return 0;
}
