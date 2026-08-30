#include <stdio.h>
#include "string_utils.h"
#include "fs_object.h"

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
    fs_object *new_dir_object = create_fs_object(new_dir, NULL);
    parent_dir->children = realloc(parent_dir->children, sizeof(fs_object) * (parent_dir->children_count + 1));
    parent_dir->children[parent_dir->children_count] = new_dir_object;
    parent_dir->children_count = parent_dir->children_count + 1;
}

void chdir(char *name, directory **current_dir_mut)
{
    // directory *current_dir_pointer = *current_dir_mut;

    for (size_t i = 0; i < (*current_dir_mut)->children_count; i++)
    {
        if (strcmp(fs_object_name(*((*current_dir_mut)->children[i])), name) == 0)
        {
            fs_object_type type = (*current_dir_mut)->children[i]->type;
            if (type == DIRECTORY_TYPE)
            {
                (*current_dir_mut) = (*current_dir_mut)->children[i]->data.directory;
                return;
            }
            else
            {
                return;
            }
        }
    }
}

void ls(const directory parent_dir)
{
    printf("Walking directory %s\n", parent_dir.name);
    for (size_t i = 0; i < parent_dir.children_count; i++)
    {
        printf("Object name = %s\n", fs_object_name(*parent_dir.children[i]));
    }
}

void process_cmd(char *cmd, directory **current_dir)
{
    int parts_len = 0;
    char **parts = split_string(cmd, " ", &parts_len);

    if (parts_len == 0)
    {
        return;
    }
    char *cmd_name = parts[0];
    printf("CMD = %s\n", cmd_name);
    if (strcmp(cmd_name, "mkdir") == 0)
    {
        printf("Arg = %s\n", parts[1]);
        mkdir(parts[1], *current_dir);
    }
    if (strcmp(cmd_name, "cd") == 0)
    {
        printf("Arg = %s\n", parts[1]);
        chdir(parts[1], current_dir);
    }
    if (strcmp(cmd_name, "ls") == 0)
    {
        ls(**current_dir);
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
    directory root_dir = {.name = "/", .children = NULL, .children_count = 0};
    directory *current_dir = &root_dir;

    while (1)
    {
        char *cmd = NULL;
        size_t len = 0;
        printf("~ %s ", current_dir->name);
        getline(&cmd, &len, stdin);
        string_strip(cmd);
        process_cmd(cmd, &current_dir);
        fflush(stdin);
    }

    return 0;
}
