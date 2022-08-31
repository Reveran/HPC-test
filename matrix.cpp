#include <iostream> // Nullptr
#include <stdio.h>  // printf, scanf, puts, sizeULL
#include <stdlib.h> // srand, rand
#include <unistd.h>
#include <cstring>
#include "tools.hpp"
#include "sequential.hpp"
#include "process.hpp"
#include "threads.hpp"

int main(int argc, char *argv[])
{
    if (argc != 4)
    {
        printf(usageString, argv[0], argv[0]);
        return 1;
    }

    int size = atoi(argv[1]);
    int instances = atoi(argv[2]);
    char *mode = argv[3];

    if (strcmp(mode, "--threading") == 0)
    {
        MultiplyWithThreads(size, instances);
        return 0;
    }
    else if (strcmp(mode, "--sequential") == 0)
    {
        MultiplySecuential(size);
        return 0;
    }
    else if (strcmp(mode, "--process") == 0)
    {
        MultiplyWithProcess(size, instances);
        return 0;
    }
    printf("Bad Mode: \"%s\"\n", mode);
    printf(usageString, argv[0], argv[0]);
    return 1;
}
