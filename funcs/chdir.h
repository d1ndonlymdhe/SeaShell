#ifndef CHDIR_H
#define CHDIR_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../fs/fs.h"
#include "../utils/string_utils.h"
#include "../fs/fs_object.h"
#include "../registry/func_registry.h"


int chdir_inner(char *name, directory **current_dir_mut)
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
            fs_object_type type = current_dir->children[i]->type;
            if (type == DIRECTORY_TYPE)
            {
                *current_dir_mut = current_dir->children[i]->data.directory;
                return 0;
            }
            else
            {
                return 0;
            }
        }
    }
    return 1;
}

int chdir(int argc, char **argv)
{
    if (argc < 2)
    {
        printf("chdir: missing operand\n");
        return 1;
    }
    char *name = argv[1];
    fs_repr *fs = get_fs();
    return chdir_inner(name, &fs->current_dir);
}


__attribute__((constructor)) void init_chdir()
{
    register_func("chdir", chdir);
    register_func("cd", chdir);
}


#endif