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
    serv->clients = client_ctor(serv);

    if (serv->clients == NULL)
        return NULL;
    serv->clients->sockfd = accept(serv->sockfd,
        (struct sockaddr *)&serv->clients->addr, &serv->clients->addrlen);
    inet_ntoa(serv->clients->addr.sin_addr);
    int temp = ntohs(serv->clients->addr.sin_port);
    (void)temp;
    printf("New connection, socket fd is %d, ip is : %s, port : %d\n",
        serv->clients->sockfd, inet_ntoa(serv->clients->addr.sin_addr), temp);
    FD_SET(serv->clients->sockfd, readfds);
    if (serv->clients->sockfd > serv->max_sd)
        serv->max_sd = serv->clients->sockfd;
    // send_msg_connection(client, serv);
    write(serv->clients->sockfd, "Welcome, you are now connected\n", 32);
    return serv->clients;
}
