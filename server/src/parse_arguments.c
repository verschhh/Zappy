/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** parse_arguments.c
*/

#include "../includes/server.h"

args_t *args_constructor(void)
{
    args_t *args = malloc(sizeof(args_t));

    args->names = malloc(sizeof(char *) * MAX_NAMES);
    args-> port = 0;
    args->namesCount = 0;
    args->height = 10;
    args->width = 10;
    args->clientsNb = 5;
    args->freq = 100;

    return args;
}

int parse_names(int ac, char **av, args_t *args)
{
    int currentArg = optind - 1;
    while (currentArg < ac && *av[currentArg] != '-') {
        args->names[args->namesCount] = strdup(av[currentArg]);
        args->namesCount++;
        currentArg++;
    }
    optind = currentArg;
    return 0;
}

int parse_default(void)
{
    if (optopt == 'p' || optopt == 'x' || optopt == 'y'
        || optopt == 'n' || optopt == 'c' || optopt == 'f') {
        fprintf(stderr, "Option -%c requires an argument.\n",
            optopt);
    } else {
        fprintf(stderr, "Unknown option `-%c'.\n", optopt);
    }
    return 84;
}

int parse_arguments(int ac, char **av, args_t *args)
{
    int option = 0;
    while ((option = getopt(ac, av, "p:x:y:n:c:f:")) != -1) {
        switch (option) {
            case 'p':
                if ((args->port = atoi(optarg)) < 1)
                    print_and_exit("Port must be greater than 0");
                break;
            case 'x':
                if ((args->width = atoi(optarg)) < 1)
                    print_and_exit("Width must be greater than 0");
                break;
            case 'y':
                if ((args->height = atoi(optarg)) < 1)
                    print_and_exit("Height must be greater than 0");
                break;
            case 'n':
                parse_names(ac, av, args);
                break;
            case 'c':
                if ((args->clientsNb = atoi(optarg)) < 1)
                    print_and_exit("ClientsNb must be greater than 0");
                break;
            case 'f':
                char *endptr;
                if ((args->freq = strtof(optarg, &endptr)) <= 0)
                    print_and_exit("Freq must be greater than 0");
                break;
            default:
                return parse_default();
        }
    }

    if (args->port == 0)
        print_and_exit("You must specify a port");

    if (args->namesCount < 2)
        print_and_exit("You must specify at least 2 team names");

    return 0;
}
