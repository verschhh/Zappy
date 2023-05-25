/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** main.c
*/

#include "../includes/server.h"

void usage(void)
{
    printf("USAGE: ./zappy_server -p port -x width -y height ");
    printf("-n name1 name2 ... -c clientsNb\n");
    printf("-f freq\n");
    printf("\tport\tis the port number\n");
    printf("\twidth\tis the width of the world\n");
    printf("\theight\tis the height of the world\n");
    printf("\tnameX\tis the name of the team X\n");
    printf("\tclientsNb\tis the number of authorized clients per team\n");
    printf("\tfreq\tis the reciprocal of time unit ");
    printf("for execution of actions\n");
}

int main(int ac, char **av)
{
    if (ac == 2 && strcmp(av[1], "-help") == 0) {
        usage();
        return 0;
    }

    args_t *args = malloc(sizeof(args_t));

    if (parse_arguments(ac, av, args) == 84) {
        return 84;
    }

    printf("port: %d, width: %d, height: %d, clientsNb: %d, freq: %.2f\n",
    args->port, args->width, args->height, args->clientsNb, args->freq);

    printf("Count: %d\n", args->namesCount);

    for (int i = 0; i < args->namesCount; i++) {
        printf("Name %d: %s\n", i + 1, args->names[i]);
    }
}
