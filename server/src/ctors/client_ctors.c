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
    return serv->clients;
}

void fill_client_struct(int sockfd, serv_t *serv, char *buffer)
{
    client_t *new_node = malloc(sizeof(client_t));

    if (new_node == NULL)
        return;
    new_node->team_name = strdup(buffer);
    new_node->sockfd = sockfd;
    new_node->player = player_ctor(serv);
    new_node->tickleft = 0;
    new_node->cpy_buffer = NULL;
    new_node->next = NULL;

    if (serv->clients == NULL) {
        serv->clients = new_node;
    } else {
        client_t *temp = serv->clients;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = new_node;
    }
}
