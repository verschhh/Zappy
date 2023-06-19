/*
** EPITECH PROJECT, 2022
** Zappy
** File description:
** accept_client.c
*/

#include "../includes/zappy.h"

client_t *accept_new_client(fd_set *readfds, serv_t *serv)
{
    struct sockaddr_in addr;
    socklen_t addrlen = sizeof(struct sockaddr_in);
    int sockfd = accept(serv->sockfd,
        (struct sockaddr *)&addr, &addrlen);

    inet_ntoa(addr.sin_addr);
    FD_SET(sockfd, readfds);
    if (sockfd > serv->max_sd)
        serv->max_sd = sockfd;
    write(sockfd, "Welcome, you are now connected\n", 32);
    return serv->clients;
}
