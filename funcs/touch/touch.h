#ifndef TOUCH_H
#define TOUCH_H

#include "../../fs/fs_object.h"

int touch_inner(char *name, directory *parent_dir);

int touch(int argc, char **argv);

void init_touch();
#endif