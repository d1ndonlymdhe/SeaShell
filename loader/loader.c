#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <stdbool.h>

#include "loader.h"
#include "../utils/string_utils.h"

bool load_so(lib_entry entry)
{
    char *lib_path = entry.lib_path;
    char *init_func_name = entry.init_func_name;
    void *handle = dlopen(lib_path, RTLD_LAZY);
    if (!handle)
    {
        fprintf(stderr, "Error loading library %s: %s\n", lib_path, dlerror());
        return false;
    }
    void (*init_func)(void) = dlsym(handle, init_func_name);
    if (!init_func)
    {
        fprintf(stderr, "Error finding init function %s in library %s: %s\n", init_func_name, lib_path, dlerror());
        dlclose(handle);
        return false;
    }
    init_func();
    return true;
}

void load_lib(lib_entry entry)
{
    if (load_so(entry))
    {
        add_entry(entry);
    }
}

lib_registry *get_lib_registry()
{
    static size_t initialized = 0;
    static lib_registry *registry;
    if (initialized == 0)
    {
        registry = malloc(sizeof(lib_registry));
        if (registry != NULL)
        {
            registry->entries = NULL;
            registry->count = 0;
            initialized = 1;
        }
    }
    return registry;
}


void add_entry(lib_entry entry)
{
    lib_registry *registry = get_lib_registry();
    registry->count++;
    registry->entries = realloc(registry->entries, sizeof(lib_entry) * (registry->count));
    registry->entries[registry->count - 1] = entry;
    save_lib_registry();
}


/**
 * LIB FILE FORMAT
 * <count>[NEW_LINE]
 * <lib_path>[TAB]<init_func_name>[NEW_LINE]
 * .....
 * */

void save_lib_registry()
{
    lib_registry *registry_pointer = get_lib_registry();
    lib_registry registry = *registry_pointer;
    const char *filename = "lib_registry.txt";
    FILE *file = fopen(filename, "w");
    // printf("%zu\n", registry.count);
    fprintf(file, "%zu\n", registry.count);
    for (size_t i = 0; i < registry.count; i++)
    {
        lib_entry entry = registry.entries[i];
        // printf("%s\t%s\n", entry.lib_path, entry.init_func_name);
        fprintf(file, "%s\t%s\n", entry.lib_path, entry.init_func_name);
    }
    fclose(file);
}

void load_lib_registry()
{
    const char *filename = "lib_registry.txt";
    FILE *file = fopen(filename, "r");
    lib_registry *init_registry = get_lib_registry();
    if (file == NULL)
    {
        // Do nothing
        return;
    }
    else
    {
        size_t len = 0;
        char *line = NULL;
        getline(&line, &len, file);
        // Read first line as number
        size_t count = strtol(line, NULL, 10);
        // If the first line is invalid count will be 0
        lib_entry *entries = NULL;
        if (count <= 0)
        {
            // do nothing
        }
        else
        {
            lib_entry *entries = malloc(sizeof(lib_entry) * count);
            size_t real_count = 0;
            for (size_t i = 0; i < count; i++)
            {
                size_t r = getline(&line, &len, file);
                if (r == EOF)
                {
                    break;
                }
                else
                {
                    string_strip(line);
                    int words = 0;
                    char **parts = split_string(line, "\t", &words);
                    if (words != 2)
                    {
                        continue;
                    }
                    else
                    {
                        real_count++;
                        lib_entry entry = {
                            .lib_path = parts[0],
                            .init_func_name = parts[1]};
                        load_so(entry);
                        entries[i].lib_path = parts[0];
                        entries[i].init_func_name = parts[1];
                    }
                }
            }
            entries = realloc(entries, sizeof(lib_entry) * real_count);
            init_registry->count = real_count;
            init_registry->entries = entries;
            return;
        }
    }
}
