/*
** EPITECH PROJECT, 2022
** Zappy
** File description:
** map.c
*/

#include "../../includes/server.h"

int map_command(int sockfd, serv_t *serv)
{
    char msg[11];

    sprintf(msg, "%s %d %d\n", "msz", serv->map_x, serv->map_y);
    if (write(sockfd, msg, 11) == -1)
        return 84;
    return 0;
}