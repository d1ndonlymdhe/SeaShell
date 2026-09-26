#ifndef LS_H
#define LS_H

#include <stdio.h>

#include "../../fs/fs_object.h"


int ls_inner(const directory parent_dir);
int ls(int argc, char **argv);
void init_ls();

#endif