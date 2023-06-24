/*
** EPITECH PROJECT, 2022
** Zappy
** File description:
** creation_client.c
*/

#include "../../includes/zappy.h"

int init_new_client(serv_t *serv, char *buffer, int cmd, int sockfd)
{
    int next = 0;

    if (cmd == -1) {
        next = check_name_team(serv, buffer);
        if (next >= 0) {
            fill_client_struct(sockfd, serv, buffer);
            send_x_y_ai(sockfd, serv, next);
            send_connection_msg(serv->clients, serv);
        } else
            write(sockfd, "suc\n", 4);
        return 1;
    }
    return 0;
}

int change_node(client_t **client, client_t *current,
    client_t *previous, int value)
{
    if (current->player->id == value) {
        if (previous == NULL)
            *client = current->next;
        else
            previous->next = current->next;
        free(current);
        return 1;
    }
    return 0;
}
