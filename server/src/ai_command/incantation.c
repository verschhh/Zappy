/*
** EPITECH PROJECT, 2022
** Zappy
** File description:
** incantation.c
*/

#include "../../includes/zappy.h"

int incantation(int sockfd, serv_t *serv, char *buffer)
{
    (void)buffer;
    client_t *client = get_correct_client(serv, sockfd);
    char msg[19];

    write(sockfd, "Elevation underway\n", 20);
    if (!client->clocking)
        update_time_limit(serv, client, 7, buffer);
    if (client->clocking) {
        client->player->level += 1;
        sprintf(msg, "Current level: %d\n", client->player->level);
        write(sockfd, msg, 19);
    }
    return 0;
}