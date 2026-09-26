#ifndef FUNC_REGISTRY
#define FUNC_REGISTRY

#include <string.h>
#include <stdlib.h>

typedef int (*func_type)(int argc, char **argv);

typedef struct func_registry_entry
{
    char *name;
    func_type func;
} func_registry_entry;

typedef struct func_registry
{
    size_t length;
    func_registry_entry *items;
} func_registry;


func_registry *get_registry();
func_registry_entry *get_func(const char *name);

void register_func(char *name, int (*func)(int argc, char **argv));


#endif
