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
    char msg[25];

    if (!client->clocking) {
        write(sockfd, "Elevation underway\n", 20);
        update_time_limit(serv, client, 300, buffer);
        return 0;
    }
    client->clocking = false;
    client->player->level += 1;
    sprintf(msg, "Current level: %d\n", client->player->level);
    printf("Level = %d\n", client->player->level);
    write(sockfd, msg, 17);
    return 0;
}