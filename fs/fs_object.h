#ifndef FS_OBJECT_H
#define FS_OBJECT_H

typedef enum fs_object_type
{
    FILE_TYPE,
    DIRECTORY_TYPE
} fs_object_type;

struct file;
struct directory;

typedef union fs_object_union
{
    struct file *file;
    struct directory *directory;
} fs_object_union;
const size_t FS_UNION_SIZE = sizeof(fs_object_union);

typedef struct fs_object
{
    fs_object_type type;
    fs_object_union data;
} fs_object;
const size_t FS_OBJECT_SIZE = sizeof(fs_object);

typedef struct file
{
    char *name;
    char *contents;
    size_t content_size;
} file;
const size_t FILE_OBJECT_SIZE = sizeof(file);

typedef struct directory
{
    char *name;
    struct directory *parent_dir;
    fs_object **children;
    size_t children_count;
} directory;
const size_t DIRECTORY_OBJECT_SIZE = sizeof(directory);

char *fs_object_name(const fs_object object)
{
    switch (object.type)
    {
    case FILE_TYPE:
        return object.data.file->name;
    case DIRECTORY_TYPE:
        return object.data.directory->name;
    }
}

/**
 * Get array of names of children both file and directories
 */
char **children_names(const directory parent_dir)
{
    if (parent_dir.children_count == 0)
    {
        return NULL;
    }
    char **object_names = calloc(sizeof(char *), parent_dir.children_count);
    for (size_t i = 0; i < parent_dir.children_count; i++)
    {
        object_names[i] = fs_object_name(*parent_dir.children[i]);
    }
    return object_names;
}

directory *create_dir(const char *dir_name, directory *parent_dir)
{
    char *name = malloc(sizeof(char) * (strlen(dir_name) + 1));
    strcpy(name, dir_name);
    directory *dir = malloc(DIRECTORY_OBJECT_SIZE * 1);
    dir->name = name;
    dir->children = NULL;
    dir->children_count = 0;
    dir->parent_dir = parent_dir;
    return dir;
}

void delete_fs_object(fs_object obj)
{
    if (obj.type == DIRECTORY_TYPE)
    {
        for (size_t i = 0; i < obj.data.directory->children_count; i++)
        {
            directory *child = obj.data.directory->children[i]->data.directory;
            delete_fs_object(*obj.data.directory->children[i]);
            free(child->name);
            free(child->children);
        }
    }
    if (obj.type == FILE_TYPE)
    {
        file *child = obj.data.file;
        free(child->name);
        free(child->contents);
    }
}

fs_object *create_fs_object(directory *directory, file *file)
{
    fs_object_union *object_union = malloc(FS_UNION_SIZE);
    fs_object_type type;
    if (directory != NULL)
    {
        object_union->directory = directory;
        type = DIRECTORY_TYPE;
    }
    if (file != NULL)
    {
        object_union->file = file;
        type = FILE_TYPE;
    }
    fs_object *object = malloc(FS_OBJECT_SIZE);
    object->type = type;
    object->data = *object_union;
    return object;
}

#endif