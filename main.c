#include <stdio.h>

#include "utils/string_utils.h"

#include "fs/fs_object.h"
#include "fs/fs.h"

#include "registry/func_registry.h"
#include "funcs/mkdir/mkdir.h"
#include "funcs/ls/ls.h"
#include "funcs/chdir/chdir.h"
#include "funcs/rmdir/rmdir.h"
#include "funcs/echo/echo.h"

void process_cmd(char *cmd)
{
    int parts_len = 0;
    char **parts = split_string(cmd, " ", &parts_len);

    if (parts_len == 0)
    {
        return;
    }
    char *cmd_name = parts[0];
    func_registry_entry *f = get_func(cmd_name);
    if (f != NULL)
    {
        int (*func)(int argc, char **argv) = f->func;
        func(parts_len, parts);
    }
    else
    {
        printf("Command not found: %s\n", cmd_name);
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

    init_echo();
    init_ls();
    init_mkdir();
    init_chdir();
    init_rmdir();

    fs_repr *fs = get_fs();

    while (1)
    {
        char *cmd = NULL;
        size_t len = 0;
        if (strcmp(fs->current_dir->name, "/") == 0)
        {
            printf("~ ");
        }
        else
        {
            printf("~ %s ", fs->current_dir->name);
        }
        getline(&cmd, &len, stdin);
        string_strip(cmd);
        process_cmd(cmd);
    }

    return 0;
}
