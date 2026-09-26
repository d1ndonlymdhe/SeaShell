#ifndef MKDIR_H
#define MKDIR_H

#include "../../fs/fs_object.h"

int mkdir_inner(char *name, directory *parent_dir);

int mkdir(int argc, char **argv);

void init_mkdir();
#endif