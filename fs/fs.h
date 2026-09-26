#ifndef FS_H
#define FS_H
#include "fs_object.h"

#include <stdlib.h>

typedef struct fs_repr
{
    directory *root_dir;
    directory *current_dir;
} fs_repr;

fs_repr *get_fs();

#endif