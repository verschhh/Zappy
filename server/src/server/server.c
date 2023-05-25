/*
** EPITECH PROJECT, 2022
** Zappy
** File description:
** server.c
*/

#include "../includes/server.h"

int server(fd_set *readfds, serv_t *serv)
{
    fd_set tmpfds;
    tmpfds = *readfds;

    if (select(serv->max_sd + 1, &tmpfds, NULL, NULL, NULL) < 0)
        print_and_exit("ERROR on select");

    for (int i = 0; i <= serv->max_sd; i++) {
        if (!FD_ISSET(i, &tmpfds)) {
            continue;
        }
        if (i == serv->sockfd) {
            accept_new_client(readfds, serv);
        } else {
            retrieve_command(i, readfds, serv);
        }
    }
}

int start_server(args_t *args)
{
    serv_t *serv = serv_ctor(args);
    fd_set readfds;
    if (serv == NULL) {
        free(args);
        return 84;
    }
    FD_SET(serv->sockfd, &readfds);
    serv->max_sd = serv->sockfd;
    while (1)
        server(&readfds, serv);
    free(args);
    return 0;
}
