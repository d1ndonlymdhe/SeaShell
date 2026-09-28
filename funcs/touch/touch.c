#include <stdio.h>

#include "touch.h"
#include "../../fs/fs_object.h"
#include "../../fs/fs.h"
#include "../../registry/func_registry.h"

// FOR NOW ALL FILES WILL HAVE THE SAME CONTENT: "ABCD"
int touch_inner(char *name, directory *parent_dir)
{
    if (object_exists(name, *parent_dir))
    {
        return 1;
    }
    file *new_file = create_file(name, "ABCD");
    fs_object *new_dir_object = create_fs_object(NULL, new_file);
    parent_dir->children = (fs_object **)realloc(parent_dir->children, sizeof(fs_object) * (parent_dir->children_count + 1));
    parent_dir->children[parent_dir->children_count] = new_dir_object;
    parent_dir->children_count = parent_dir->children_count + 1;
    return 0;
}

int touch(int argc, char **argv)
{
    if (argc < 2)
    {
        printf("touch: missing operand\n");
        return 1;
    }
    char *name = argv[1];
    fs_repr *fs = get_fs();
    return touch_inner(name, fs->current_dir);
}

void init_touch()
{
    printf("Registering touch function\n");
    register_func("touch", touch);
}