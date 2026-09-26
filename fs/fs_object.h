#ifndef FS_OBJECT_H
#define FS_OBJECT_H

#include <stdlib.h>
#include <string.h>

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
extern const size_t FS_UNION_SIZE;
typedef struct fs_object
{
    fs_object_type type;
    fs_object_union data;
} fs_object;
extern const size_t FS_OBJECT_SIZE;

typedef struct file
{
    char *name;
    char *contents;
    size_t content_size;
} file;
extern const size_t FILE_OBJECT_SIZE;

typedef struct directory
{
    char *name;
    struct directory *parent_dir;
    fs_object **children;
    size_t children_count;
} directory;
extern const size_t DIRECTORY_OBJECT_SIZE;

char *fs_object_name(const fs_object object);

/**
 * Get array of names of children both file and directories
 */
char **children_names(const directory parent_dir);

directory *create_dir(const char *dir_name, directory *parent_dir);

void delete_fs_object(fs_object obj);

fs_object *create_fs_object(directory *directory, file *file);

#endif