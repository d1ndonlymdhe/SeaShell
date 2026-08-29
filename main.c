#include <stdio.h>
#include "string_utils.h"
#include "fs_object.h"

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

void mkdir(char *name, directory *parent_dir)
{

    if (parent_dir->children_count != 0)
    {
        char **object_names = children_names(*parent_dir);
        for (size_t i = 0; i < parent_dir->children_count; i++)
        {
            if (strcmp(object_names[i], name) == 0)
            {
                return;
            }
        }
    }
    else
    {
        parent_dir->children = malloc(sizeof(fs_object));
    }

    directory *new_dir = create_dir(name, parent_dir);
    fs_object *new_dir_object = create_object(new_dir, NULL);
    parent_dir->children = realloc(parent_dir->children, sizeof(fs_object) * (parent_dir->children_count + 1));
    parent_dir->children[parent_dir->children_count] = new_dir_object;
    parent_dir->children_count = parent_dir->children_count + 1;
}

int main()
{
    char *dir = "/";
    directory root_dir = {.name = "/", .children = NULL, .children_count = 0};
    mkdir("hello", &root_dir);
    mkdir("there", &root_dir);
    mkdir("kenobi", &root_dir);

    walk_directory(root_dir);
    return 0;
}
