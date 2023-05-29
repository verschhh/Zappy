/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** main.c
*/

#include "../includes/server.h"

int main(int ac, char **av)
{
    if (ac == 2 && strcmp(av[1], "-help") == 0) {
        usage();
        return 0;
    }

    args_t *args = args_constructor();
    if (parse_arguments(ac, av, args) == 84) {
        free(args);
        return 84;
    }
    start_server(args);
}

/*
    printf("port: %d, width: %d, height: %d, clientsNb: %d, freq: %.2f\n",
    args->port, args->width, args->height, args->clientsNb, args->freq);

    printf("Count: %d\n", args->namesCount);

    for (int i = 0; i < args->namesCount; i++) {
        printf("Name %d: %s\n", i + 1, args->names[i]);
    }
*/