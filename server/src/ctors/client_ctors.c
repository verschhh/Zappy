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
    if (serv->clients == NULL) {
        serv->clients = malloc(sizeof(client_t));
        serv->clients->next = NULL;
    }
    while (serv->clients->next != NULL)
        serv->clients = serv->clients->next;
    serv->clients->addrlen = sizeof(struct sockaddr_in);
    serv->clients->slot = serv->slots->nb;
    serv->clients->next = NULL;
    printf("POV: J'ME SUIS CREE\n");
    return serv->clients;
}

int fill_client_struct(int sockfd, serv_t *serv, char *buffer)
{
    client_t *temp = serv->clients;
    client_t *new_node = malloc(sizeof(client_t));

    if (new_node == NULL)
        return 84;

    new_node->next = NULL;
    new_node->sockfd = sockfd;
    new_node->player = player_ctor(serv);
    printf("payer #%d\n", new_node->player->id);
    new_node->slot -= 1;
    new_node->team_name = buffer;

    if (temp == NULL) {
        serv->clients = new_node;
    } else {
        while (temp->next != NULL || temp->sockfd != sockfd)
            temp = temp->next;
        temp->next = new_node;
    }

    return 0;
}
// {
//     client_t *temp = serv->clients;

//     while(temp->next != NULL || temp->sockfd != sockfd)
//         temp = temp->next;
//     if (temp->sockfd == sockfd) {
//         temp->player = player_ctor(serv);
//         temp->slot -= 1;
//         temp->team_name = buffer;
//     }
//     // send_connection_msg(temp);
// }
