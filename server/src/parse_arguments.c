/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** parse_arguments.c
*/

#include "../includes/server.h"

int parse_arguments(int ac, char **av, args_t *args)
{
    int option = 0;

    args->names = malloc(sizeof(char *) * MAX_NAMES);
    args->namesCount = 0;

    while ((option = getopt(ac, av, "p:x:y:n:c:f:")) != -1) {
        switch (option) {
            case 'p':
                args->port = atoi(optarg);
                break;
            case 'x':
                args->width = atoi(optarg);
                break;
            case 'y':
                args->height = atoi(optarg);
                break;
            case 'n':
                int currentArg = optind - 1;
                while (currentArg < ac && *av[currentArg] != '-') {
                    args->names[args->namesCount] = strdup(av[currentArg]);
                    args->namesCount++;
                    currentArg++;
                }
                optind = currentArg;
                break;
            case 'c':
                args->clientsNb = atoi(optarg);
                break;
            case 'f':
                args->freq = atoi(optarg);
                break;
            case '?':
                if (optopt == 'p' || optopt == 'x' || optopt == 'y' || optopt == 'n' || optopt == 'c' || optopt == 'f') {
                    fprintf(stderr, "Option -%c requires an argument.\n", optopt);
                } else {
                    fprintf(stderr, "Unknown option `-%c'.\n", optopt);
                }
            default:
                printf("default\n");
                return 84;
        }
    }

    printf("port: %d, width: %d, height: %d, clientsNb: %d, freq: %d\n",
    args->port, args->width, args->height, args->clientsNb, args->freq);

    printf("Count: %d\n", args->namesCount);

    for (int i = 0; i < args->namesCount; i++) {
        printf("Name %d: %s\n", i + 1, args->names[i]);
    }

    return 0;
}
