#include <stdio.h>

#include "ls.h"
#include "../../fs/fs_object.h"
#include "../../fs/fs.h"
#include "../../registry/func_registry.h"

int ls_inner(const directory parent_dir)
{
    printf("Walking directory %s\n", parent_dir.name);
    for (size_t i = 0; i < parent_dir.children_count; i++)
    {
        printf("Object name = %s\n", fs_object_name(*parent_dir.children[i]));
    }
    return 0;
}
int ls(int argc, char **argv)
{
    fs_repr *fs = get_fs();
    const directory *parent_dir = fs->current_dir;
    if (parent_dir == NULL)
    {
        printf("Error: current directory is NULL\n");
        return 1;
    }
    return ls_inner(*parent_dir);
}

void init_ls()
{
    printf("Registering ls function\n");
    register_func("ls", ls);
}