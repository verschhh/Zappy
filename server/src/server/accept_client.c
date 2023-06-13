/*
** EPITECH PROJECT, 2022
** Zappy
** File description:
** accept_client.c
*/

#include "../includes/zappy.h"

void send_msg_connection(client_t *client, serv_t *serv)
{
    char *msg;
    int len = snprintf(msg, 0, "pnw #%d %d %d", client->player->x, client->player->y);

    msg = malloc(sizeof(char) * (len + 1));
    msg[len] = '\0';
    sprintf(msg, "pnw #%d %d %d", client->player->x, client->player->y);
    write(serv->sockfd, msg, len);
}

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
