/*
** EPITECH PROJECT, 2022
** Zappy
** File description:
** client_ctors.c
*/

#include "../includes/zappy.h"

client_t *pop_client(client_t *client)
{
    client_t *tmp = client;

    if (client == NULL)
        return NULL;
    while (tmp->next != NULL)
        tmp = tmp->next;
    free(tmp);
    return client;
}

client_t *client_ctor(serv_t *serv)
{
    if (serv->clients == NULL)
        serv->clients = malloc(sizeof(client_t));
    while (serv->clients->next != NULL)
        serv->clients = serv->clients->next;
    serv->clients->addrlen = sizeof(struct sockaddr_in);
    serv->clients->next = NULL;
    return serv->clients;
}

int fill_client_struct(int sockfd, serv_t *serv, char *buffer)
{
    client_t *temp = serv->clients;

    while(temp->next != NULL || temp->sockfd != sockfd)
        temp = temp->next;
    if (temp->sockfd == sockfd) {
        temp->player = player_ctor(serv);
        temp->slot -= 1;
        temp->team_name = buffer;
    }
    
}
