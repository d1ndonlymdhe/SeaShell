#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>

typedef struct lib_entry
{
    char *lib_path;
    char *init_func_name;
} lib_entry;

typedef struct lib_registry
{
    lib_entry *entries;
    ;
    size_t count;
} lib_registry;

void load_lib(lib_entry entry);

extern lib_registry *get_lib_registry();

void add_entry(lib_entry entry);

/**
 * LIB FILE FORMAT
 * <count>[NEW_LINE]
 * <lib_path>[TAB]<init_func_name>[NEW_LINE]
 * .....
 * */

void save_lib_registry();

void load_lib_registry();
