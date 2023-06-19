/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** parse_arguments.c
*/

#include "../../includes/zappy.h"

args_t *args_constructor(void)
{
    args_t *args = malloc(sizeof(args_t));

    args->names = malloc(sizeof(char *) * MAX_NAMES);
    args-> port = 0;
    args->namescount = 0;
    args->height = 10;
    args->width = 10;
    args->clientsnb = 6;
    args->freq = 2;

    return args;
}

static void arguments_error_handling(args_t *args)
{
    if (args->port == 0)
        print_and_exit("You must specify a port");

    if (args->namescount < 2)
        print_and_exit("You must specify at least 2 team names");
}

int parse_arguments(int ac, char **av, args_t *args)
{
    int option = 0;
    while ((option = getopt(ac, av, "p:x:y:n:c:f:")) != -1) {
        switch (option) {
            case 'p':
            case 'x':
            case 'y':
                parse_port_width_height(option, optarg, args);
                break;
            case 'n':
            case 'c':
            case 'f':
                parse_names_clients_nb_freq(option, optarg, args, av);
                break;
            default:
                return parse_default();
        }
    }
    arguments_error_handling(args);
    return 0;
}
