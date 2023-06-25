/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** parse_flags.c
*/

#include "../includes/zappy.h"

int parse_names(char **av, args_t *args)
{
    int ac = 0;
    int len = 0;

    for (ac = 0; av[ac] != NULL; ac++);
    int currentArg = optind - 1;
    while (currentArg < ac && *av[currentArg] != '-') {
        args->names[args->namescount] = strdup(av[currentArg]);
        args->names[args->namescount][strlen(av[currentArg])] = 0;
        args->namescount++;
        currentArg++;
        len++;
    }
    args->names[len] = NULL;
    optind = currentArg;
    return 0;
}

int parse_port_width_height(int option, char *optarg, args_t *args)
{
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
    }
    return 0;
}

int parse_names_clients_nb_freq(int option, char *optarg, args_t *args,
    char **av)
{
    switch (option) {
        case 'n':
            parse_names(av, args);
            break;
        case 'c':
            if ((args->clientsnb = atoi(optarg)) < 1)
                print_and_exit("ClientsNb must be greater than 0");
            break;
        case 'f':
            char *endptr;
            if ((args->freq = strtof(optarg, &endptr)) <= 0 ||
                (args->freq = strtof(optarg, &endptr)) > 100)
                print_and_exit("Freq must <0, 100>");
            break;
    }
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
