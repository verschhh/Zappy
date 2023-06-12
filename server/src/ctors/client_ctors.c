/*
** EPITECH PROJECT, 2022
** Zappy
** File description:
** client_ctors.c
*/

#include "../includes/zappy.h"

client_t *pop_client(client_t **client)
{
    client_t* temp = *client;

    if (temp == NULL)
        return NULL;
    *client = temp->next;
    free(temp);
    return *client;
}

client_t *client_ctor(serv_t *serv)
{
    serv->clients = malloc(sizeof(client_t));
    serv->clients->addrlen = sizeof(struct sockaddr_in);
    serv->clients->slot = serv->slots->nb;
    serv->clients->next = NULL;
    serv->clients->next = NULL;
    return serv->clients;
}

client_t *fill_client_struct(int sockfd, serv_t *serv, char *buffer)
{
    client_t *temp = serv->clients;
    client_t *new_node = malloc(sizeof(client_t));

    if (new_node == NULL)
        return NULL;
    new_node->next = NULL;
    new_node->sockfd = sockfd;
    new_node->player = player_ctor(serv);
    new_node->slot -= 1;
    new_node->team_name = buffer;

    if (temp == NULL) {
        serv->clients = new_node;
    } else {
        while (temp->next != NULL || temp->sockfd != sockfd)
            temp = temp->next;
        temp->next = new_node;
    }

    return serv->clients;
}
