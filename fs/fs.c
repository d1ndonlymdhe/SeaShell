#include "fs_object.h"
#include "fs.h"
#include <stdlib.h>

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
