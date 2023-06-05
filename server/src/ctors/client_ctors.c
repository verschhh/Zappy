/*
** EPITECH PROJECT, 2022
** Zappy
** File description:
** client_ctors.c
*/

#include "../includes/server.h"

void fill_new_node(client_t *new_node, args_t *arg, int i)
{
    new_node->team_name = arg->names[i];
    new_node->addrlen = sizeof(struct sockaddr_in);
    new_node->next = NULL;
    new_node->slot = arg->clientsnb;
    new_node->player = player_root_ctor(0);
    for (int j = 1; j != arg->clientsnb; j++)
        add_player(new_node->player);
}

client_t *root_client_ctor(args_t *arg)
{
    client_t *root = NULL;
    client_t *current = NULL;

    for (int i = 0; i != arg->namescount; i++) {
        client_t *new_node = malloc(sizeof(client_t));
        if (new_node == NULL)
            perror("Memory allocation failed");
        fill_new_node(new_node, arg, i);
        if (root == NULL) {
            root = new_node;
            current = root;
        } else {
            current->next = new_node;
            current = current->next;
        }
    }
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

client_t *create_client(client_t *root)
{
    root = malloc(sizeof(client_t));
    root->team_name = "TEMP";
    root->next = NULL;
}

client_t *client_ctor(serv_t *serv)
{
    client_t *root = NULL;
    client_t *current = NULL;

    if (serv->clients == NULL) {
        create_client(root);
        return root;
    }
    // while (serv->clients->next != NULL)
    //     map_t *new_node = malloc(sizeof(map_t));
    //     if (new_node == NULL)
    //         perror("Memory allocation failed");
    //     fill_new_node_map(new_node, arg);
    //     if (root == NULL) {
    //         root = new_node;
    //         current = root;
    //     } else {
    //         current->next = new_node;
    //         current = current->next;
    //     }
    // }
    return root;
}
