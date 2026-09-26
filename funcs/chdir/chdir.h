#ifndef CHDIR_H
#define CHDIR_H

#include "../../fs/fs_object.h"

int chdir_inner(char *name, directory **current_dir_mut);

int chdir(int argc, char **argv);

void init_chdir();
#endif