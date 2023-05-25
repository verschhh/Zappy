/*
** EPITECH PROJECT, 2022
** Zappy
** File description:
** accept_client.c
*/

#include "../includes/server.h"

void accept_new_client(fd_set *readfds, serv_t *serv)
{
    client_t *client = client_ctor(serv->clients);
    client->sockfd = accept(serv->sockfd,
        (struct sockaddr *)&client->addr, &client->addrlen);
    inet_ntoa(client->addr.sin_addr);
    int temp = ntohs(client->addr.sin_port);
    (void)temp;
    FD_SET(client->sockfd, readfds);
    if (client->sockfd > serv->max_sd)
        serv->max_sd = client->sockfd;
}
