#ifndef RMDIR_H
#define RMDIR_H


#include "../../fs/fs_object.h"

int rmdir_inner(char *name, directory **current_dir_mut);

int rmdir(int argc, char **argv);

void init_rmdir();
#endif