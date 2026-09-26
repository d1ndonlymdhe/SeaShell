#include <stdio.h>
#include "echo.h"
#include "../../registry/func_registry.h"

int echo_inner(char *arg)
{
    printf("%s\n", arg);
    return 0;
}

int echo(int argc, char **argv)
{
    if (argc < 2)
    {
        printf("echo: missing operand\n");
        return 1;
    }
    char *arg = argv[1];
    return echo_inner(arg);
}

void init_echo()
{
    printf("Registering echo function\n");
    register_func("echo", echo);
}
