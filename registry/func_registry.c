
#include <string.h>
#include <stdlib.h>
#include "func_registry.h"

func_registry *get_func_registry()
{
    static size_t initialized = 0;
    static func_registry *registry;
    if (initialized == 0)
    {
        registry = malloc(sizeof(func_registry));
        if (registry != NULL)
        {
            registry->items = NULL;
            registry->length = 0;
            initialized = 1;
        }
    }
    return registry;
}


func_registry_entry *get_func(const char *name)
{
    func_registry *registry = get_func_registry();
    for (size_t i = 0; i < registry->length; i++)
    {
        if (strcmp(registry->items[i].name, name) == 0)
        {
            return &registry->items[i];
        }
    }
    return NULL;
}


void register_func(char *name, int (*func)(int argc, char **argv))
{
    func_registry *registry = get_func_registry();
    func_registry_entry *entry = (func_registry_entry *)malloc(sizeof(func_registry_entry));
    entry->func = func;
    entry->name = name;
    for (size_t i = 0; i < registry->length; i++)
    {
        if (strcmp(registry->items[i].name, name) == 0)
        {
            func_registry_entry *current = &registry->items[i];
            registry->items[i].func = func;
            return;
        }
    }
    registry->length++;
    registry->items = (func_registry_entry *)realloc(registry->items, sizeof(func_registry_entry) * registry->length);
    registry->items[registry->length - 1].func = func;
    registry->items[registry->length - 1].name = name;
}
