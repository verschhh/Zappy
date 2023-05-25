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

    args_t *args = malloc(sizeof(args_t));
    if (parse_arguments(ac, av, args) == 84) {
        free(args);
        return 84;
    }
    start_server(args);
}
