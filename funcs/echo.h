#ifndef ECHO_H
#define ECHO_H
#include <stdio.h>
#include "../registry/func_registry.h"
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

__attribute__((constructor)) void init_echo()
{
    register_func("echo", echo);
}

#endif
