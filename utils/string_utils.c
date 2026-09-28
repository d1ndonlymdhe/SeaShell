
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "string_utils.h"
/**
 * Splits a string into an array of strings based on a delimiter.
 * The length of the resulting array is stored in the provided len pointer.
 * Copies the strings into new memory, so the caller is responsible for freeing the memory.
 */
char **split_string(const char *str, const char *delim, int *len)
{
    char *str_copy = malloc(sizeof(char) * (strlen(str) + 1));
    strcpy(str_copy,str);
    *len = 1;
    char **out = malloc(sizeof(char *));
    char *part = strtok(str_copy, delim);
    while (part != NULL)
    {
        out = realloc(out, (*len) * sizeof(char *));
        char *part_copy = malloc(strlen(part) + 1);
        strcpy(part_copy, part);
        out[(*len) - 1] = part_copy;
        part = strtok(NULL, delim);
        (*len)++;
    }
    (*len)--;
    free(part);
    return out;
}

char *str_dup(const char *str)
{
    size_t len = strlen(str);
    char *copy = malloc(len + 1);
    if (copy != NULL)
    {
        strcpy(copy, str);
    }
    return copy;
}

/**
 * Strips leading and trailing whitespace inplace.
 */
void string_strip(char *str)
{
    int start_from = 0;
    int len = 0;
    for (int i = 0; i < strlen(str); i++)
    {
        if (!isspace(str[i]))
        {
            start_from = i;
            break;
        }
    };
    int end_at = strlen(str) - 1;
    for (int i = strlen(str) - 1; i >= 0; i--)
    {
        if (!isspace(str[i]))
        {
            end_at = i;
            break;
        }
    }
    str[end_at + 1] = '\0';
    for (size_t i = 0; i < start_from; i++)
    {
        str[i] = '\0';
    }
    str = str + start_from;
}
