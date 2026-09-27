#include <stdio.h>
#include <dlfcn.h>

#include "utils/string_utils.h"

#include "fs/fs_object.h"
#include "fs/fs.h"

#include "registry/func_registry.h"
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

void load_lib(const char *lib_path, const char *init_func_name)
{
    void *handle = dlopen(lib_path, RTLD_LAZY);
    if (!handle)
    {
        fprintf(stderr, "Error loading library %s: %s\n", lib_path, dlerror());
        return;
    }
    void (*init_func)(void) = dlsym(handle, init_func_name);
    if (!init_func)
    {
        fprintf(stderr, "Error finding init function %s in library %s: %s\n", init_func_name, lib_path, dlerror());
        dlclose(handle);
        return;
    }
    init_func();
}

int main()
{
    fs_repr *fs = get_fs();
    load_lib("./funcs/mkdir/mkdir.so", "init_mkdir");
    load_lib("./funcs/chdir/chdir.so", "init_chdir");
    load_lib("./funcs/ls/ls.so", "init_ls");
    load_lib("./funcs/rmdir/rmdir.so", "init_rmdir");
    load_lib("./funcs/echo/echo.so", "init_echo");
    while (1)
    {
        char *cmd = NULL;
        size_t len = 0;
        if (strcmp(fs->current_dir->name, "/") == 0)
        {
            printf("~ -> ");
        }
        else
        {
            printf("~ %s -> ", fs->current_dir->name);
        }
        getline(&cmd, &len, stdin);
        string_strip(cmd);
        process_cmd(cmd);
    }

    return 0;
}
