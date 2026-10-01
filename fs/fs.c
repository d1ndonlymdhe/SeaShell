#include "fs_object.h"
#include "fs.h"
#include <stdlib.h>
#include <stdio.h>
fs_repr *get_fs()
{
    static size_t initialized = 0;
    static fs_repr *fs;
    if (initialized == 0)
    {
        directory *root_dir = create_dir("/", NULL);
        fs = (fs_repr *)malloc(sizeof(fs_repr));
        fs->root_dir = root_dir;
        fs->current_dir = root_dir;
        initialized = 1;
    }
    return fs;
}

void save_file(file file, FILE *fs_file)
{
    fprintf(fs_file, "FILE %s\n", file.name);
    fprintf(fs_file, "%zu\n", file.content_size);
    fprintf(fs_file, "%s\n", file.contents);
}

void save_directory(directory dir, FILE *fs_file)
{
    fprintf(fs_file, "DIR %s\n", dir.name);
    fprintf(fs_file, "%zu\n", dir.children_count);
    for (size_t i = 0; i < dir.children_count; i++)
    {
        fs_object *child = dir.children[i];
        if (child->type == DIRECTORY_TYPE)
        {
            save_directory(*(child->data.directory), fs_file);
        }
        else if (child->type == FILE_TYPE)
        {
            save_file(*(child->data.file), fs_file);
        }
    }
}

/**
 *
 * DIR_STRUCTURE:
 * <"DIR"> <name>
 * <number_of_objects>
 * <DIR_STRUCTURE | FILE_STRUCTURE>
 * <DIR_STRUCTURE | FILE_STRUCTURE>
 * ...
 * FILE_STRUCTURE:
 * <"FILE"> <name>
 * <content_size>
 * <content>
 */
void save_fs()
{
    fs_repr fs = *(get_fs());
    FILE *fs_file = fopen("fs.txt", "w");
    save_directory(*(fs.root_dir), fs_file);
    fclose(fs_file);
}


void load_fs()
{
    FILE *fs_file = fopen("fs.txt", "r");
    if (fs_file == NULL)
    {

        return;
    }else{
        
    }
}
