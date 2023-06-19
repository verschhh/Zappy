/*
** EPITECH PROJECT, 2022
** Zappy
** File description:
** incantation.c
*/

#include "../../includes/zappy.h"

int incantation(int sockfd, serv_t *serv, char *buffer)
{
    client_t *client = get_correct_client(serv, sockfd);
    char msg[19];

    write(sockfd, "Elevation underway\n", 20);
    client->tickleft = 300;
    client->player->level += 1;
    if (client->tickleft <= 0) {
        sprintf(msg, "Current level: %d\n", client->player->level);
        write(sockfd, msg, 19);
    }
}