#ifndef STRING_UTILS_H
#define STRING_UTILS_H

#include <string.h>
#include <stdlib.h>
#include <ctype.h>
/**
 * Splits a string into an array of strings based on a delimiter.
 * The length of the resulting array is stored in the provided len pointer.
 * Copies the strings into new memory, so the caller is responsible for freeing the memory.
 */
char **split_string(const char *str, const char *delim, int *len);
/**
 * Strips leading and trailing whitespace inplace.
 */
void string_strip(char *str);

#endif