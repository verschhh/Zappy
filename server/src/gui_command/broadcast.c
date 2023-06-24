/*
** EPITECH PROJECT, 2022
** Zappy
** File description:
** broadcast.c
*/

#include "../../includes/zappy.h"

int send_broadcast(int sockfd, serv_t *serv, char *buffer)
{
    char msg[0];
    client_t *cpy = get_correct_client(serv, sockfd);
    int len = snprintf(msg, 0, "pbc %d %s", cpy->player->id, buffer);
    char send[len];
    if (buffer == NULL)
        return unknown_command(sockfd, serv, buffer);
    sprintf(send, "pbc %d %s", cpy->player->id, buffer);
    write(serv->sockfd, send, len);
    return 0;
}
