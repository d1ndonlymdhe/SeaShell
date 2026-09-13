#ifndef RMDIR_H
#define RMDIR_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../fs/fs.h"
#include "../utils/string_utils.h"
#include "../fs/fs_object.h"
#include "../registry/func_registry.h"

int rmdir_inner(char *name, directory **current_dir_mut)
{
    const directory *current_dir = *current_dir_mut;
    if (strcmp(name, "..") == 0)
    {
        if (current_dir->parent_dir != NULL)
        {
            *current_dir_mut = current_dir->parent_dir;
            return 0;
        }
    }

    for (size_t i = 0; i < current_dir->children_count; i++)
    {
        if (strcmp(fs_object_name(*(current_dir->children[i])), name) == 0)
        {
            fs_object *object = current_dir->children[i];
            delete_fs_object(*(current_dir->children[i]));
            free(object);
            (*current_dir_mut)->children_count = current_dir->children_count - 1;
            for (size_t j = i; j < current_dir->children_count - 1; j++)
            {
                current_dir->children[j] = current_dir->children[j + 1];
            }
            return 0;
        }
    }
    return 1;
}

int rmdir(int argc, char **argv)
{
    if (argc < 2)
    {
        printf("rmdir: missing operand\n");
        return 1;
    }
    char *name = argv[1];
    fs_repr *fs = get_fs();
    return rmdir_inner(name, &fs->current_dir);
}

__attribute__((constructor)) void init_rmdir()
{
    register_func("rmdir", rmdir);
    register_func("rm", rmdir);
}

#endif