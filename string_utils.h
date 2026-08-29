#include <string.h>
#include <stdlib.h>
#include <ctype.h>
/**
 * Splits a string into an array of strings based on a delimiter.
 * The length of the resulting array is stored in the provided len pointer.
 * Copies the strings into new memory, so the caller is responsible for freeing the memory.
 */
char **split_string(char *str, const char *delim, int *len)
{
    size_t delim_size = strlen(delim);
    char **out = (char **)malloc(sizeof(char *));
    char *current_word = (char *)malloc(sizeof(char));
    *len = 1;

    size_t i = 0;

    while (i < strlen(str))
    {
        size_t end = i + delim_size;
        char *delim_test = (char *)malloc((sizeof(char) * delim_size) + 1);
        memcpy(delim_test, str + i, delim_size);
        delim_test[delim_size] = '\0';
        printf("THE DELIM TEST IS: %s\n", delim_test);
        if (strcmp(delim_test, delim) == 0)
        {
            size_t current_word_len = strlen(current_word);
            if (current_word_len > 0)
            {
                char *current_word_copy = (char *)malloc(sizeof(char) * current_word_len + 1);
                memcpy(current_word_copy, current_word, current_word_len + 1);
                out[*len - 1] = current_word_copy;
                *len = *len + 1;
                out = (char **)realloc(out, (*len) * sizeof(char *));
                current_word = (char *)realloc(current_word, sizeof(char));
                current_word[0] = '\0';
            }
            i += delim_size;
        }
        else
        {
            current_word = (char *)realloc(current_word, strlen(current_word) + 2);
            strncat(current_word, str + i, 1);
            i += 1;
        }
        free(delim_test);
    }
    char *current_word_copy = (char *)malloc(sizeof(char) * strlen(current_word) + 1);
    memcpy(current_word_copy, current_word, strlen(current_word) + 1);
    out[*len - 1] = current_word_copy;
    free(current_word);
    return out;
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
    str = str + start_from;
}