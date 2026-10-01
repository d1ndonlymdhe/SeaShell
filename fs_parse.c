#include <stdio.h>
#include <string.h>
#include <stdlib.h>

size_t parse_directory(char *data, char **save_ptr, size_t offset_lines)
{
    char *clone = data;
    size_t lines_read = offset_lines;
    char *t = strtok_r(offset_lines == 0 ? clone : NULL, " ", save_ptr);
    if (t == NULL)
    {
        return lines_read;
    }
    if (strcmp(t, "DIR") == 0)
    {
        char *dir_name = strtok_r(NULL, "\n", save_ptr);
        if (dir_name == NULL)
        {
            return lines_read;
        }
        printf("Directory: %s\n", dir_name);
        lines_read++;
        char *num_children_str = strtok_r(NULL, "\n", save_ptr);
        lines_read++;
        if (num_children_str == NULL)
        {
            return lines_read;
        }
        size_t num_children = strtol(num_children_str, NULL, 10);
        for (size_t i = 0; i < num_children; i++)
        {
            size_t child_lines_read = parse_directory(data, save_ptr, lines_read);
            lines_read += child_lines_read;
        }
    }
    else if (strcmp(t, "FILE") == 0)
    {
        char *file_name = strtok_r(NULL, "\n", save_ptr);
        if (file_name == NULL)
        {
            return lines_read;
        }
        printf("File: %s\n", file_name);
        lines_read++;
        char *content_size_str = strtok_r(NULL, "\n", save_ptr);
        lines_read++;
        if (content_size_str == NULL)
        {
            return lines_read;
        }
    }
    return lines_read;
}
size_t parse_file(char *data, char **save_ptr, size_t offset_lines)
{
    char *clone = data;
    size_t lines_read = offset_lines;
    char *t = strtok_r(offset_lines == 0 ? clone : NULL, " ", save_ptr);
    if (t == NULL)
    {
        return lines_read;
    }
    if (strcmp(t, "FILE") == 0)
    {
        char *file_name = strtok_r(NULL, "\n", save_ptr);
        if (file_name == NULL)
        {
            return lines_read;
        }
        printf("File: %s\n", file_name);
        lines_read++;
        char *content_size_str = strtok_r(NULL, "\n", save_ptr);
        lines_read++;
        if (content_size_str == NULL)
        {
            return lines_read;
        }
    }
    return lines_read;
}

size_t parse_fs(char *data)
{
    char *save_ptr;

    return parse_directory(data, &save_ptr, 0);
}

char *read_entire_file(const char *filename)
{
    // 1. Open the file in binary mode to accurately count bytes
    FILE *file = fopen(filename, "rb");
    if (file == NULL)
    {
        perror("Error opening file");
        return NULL;
    }

    // 2. Move the file pointer to the end to determine the size
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    rewind(file); // Move back to the beginning of the file

    // 3. Allocate memory for the file content + 1 null-terminator byte
    char *buffer = (char *)malloc(file_size + 1);
    if (buffer == NULL)
    {
        perror("Memory allocation failed");
        fclose(file);
        return NULL;
    }

    // 4. Read the entire file block into the buffer
    size_t bytes_read = fread(buffer, 1, file_size, file);

    // 5. Add the null terminator string literal marker
    buffer[bytes_read] = '\0';

    // 6. Clean up and return
    fclose(file);
    return buffer;
}

int main()
{
    char *data = read_entire_file("fs.txt");
    if (data == NULL)
    {
        return 1; // Exit if file reading failed
    }
    size_t lines_read = parse_fs(data);
    printf("Total lines read: %zu\n", lines_read);
    free(data); // Free the allocated memory for file content
    return 0;
}