#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "mkdir.h"
#include "../../fs/fs.h"
#include "../../utils/string_utils.h"
#include "../../fs/fs_object.h"
#include "../../registry/func_registry.h"

int mkdir_inner(char *name, directory *parent_dir)
{

    if (parent_dir->children_count != 0)
    {
        if (object_exists(name, *parent_dir))
        {
            return 1;
        }
    }
    else
    {
        parent_dir->children = (fs_object **)malloc(sizeof(fs_object));
    }

    directory *new_dir = create_dir(name, parent_dir);
    fs_object *new_dir_object = create_fs_object(new_dir, NULL);
    parent_dir->children = (fs_object **)realloc(parent_dir->children, sizeof(fs_object) * (parent_dir->children_count + 1));
    parent_dir->children[parent_dir->children_count] = new_dir_object;
    parent_dir->children_count = parent_dir->children_count + 1;
    return 0;
}

int mkdir(int argc, char **argv)
{
    if (argc < 2)
    {
        printf("mkdir: missing operand\n");
        return 1;
    }
    char *name = argv[1];
    fs_repr *fs = get_fs();
    return mkdir_inner(name, fs->current_dir);
}

void init_mkdir()
{
    printf("Registering mkdir function\n");
    register_func("mkdir", mkdir);
}
