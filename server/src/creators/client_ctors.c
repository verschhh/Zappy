/*
** EPITECH PROJECT, 2022
** Zappy
** File description:
** client_ctors.c
*/

#include "../includes/server.h"

client_t *root_client_ctor(void)
{
    client_t *root = malloc(sizeof(client_t));

    root->x = 0;
    root->y = 0;
    root->level = 0;
    root->orientation = 0;
    root->team_name = NULL;
    root->next = NULL;
    root->addrlen = sizeof(struct sockaddr_in);
    return root;
}

client_t *client_ctor(client_t *root)
{
    client_t *new_client = malloc(sizeof(client_t));
    client_t *tmp = root;

    if (root == NULL)
        return NULL;
    while (tmp->next != NULL)
        tmp = tmp->next;
    new_client->addrlen = sizeof(struct sockaddr_in);
    new_client->next = NULL;
    tmp->next = new_client;
    return new_client;
}

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
